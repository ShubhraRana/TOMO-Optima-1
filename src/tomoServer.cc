#include "iostream"
#include "cstdlib"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "deque"
#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/address.h"
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/address-utils.h"
#include "ns3/nstime.h"
#include "ns3/inet-socket-address.h"
#include "ns3/socket.h"
#include "ns3/udp-socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
using namespace std;
using namespace ns3;

#define TREE 0
#define MESH 1
#define MAX_CONNECTIONS 2

//Things to do
//1. Figure out how to implement the rest of the internet stack, Ip Address, Net Devices, Channels etc.(hint: I'm
//   guessing object aggregators are used, chk 'em out!)
//2. Create the Client application to send requests, join messages , create mesh connections and forward packets when required 

//forward declaration
class treeMeshNode;
//An object to hold each connection
struct Connection
{
    Ptr<treeMeshNode> Node;
    int type;
};

//An object to hold each node information
class treeMeshNode: public Object
{
    public:
        int index;
        // A reference to the actual Node(Client)
        Ptr<Node> Nodes;
        // a list of connections
        vector<Connection> connections;

        Ptr<treeMeshNode> operator=(Ptr<treeMeshNode> right)
        {
            Ptr<treeMeshNode> left;
            this->Nodes = right->Nodes;
            this->connections = right->connections;
            return this;
        }
};

//The server Implementation - Modelled after the TOMO Paper found in the reference section of this project and
//UdpEchoServer implementation provided along with ns3
class tomoServer
{
    private:
        Ptr<treeMeshNode> Server;
        Ptr<Socket> m_socket;
        uint32_t m_port;
        Address m_local;
    public:
        tomoServer()
        {
            Server = CreateObject<treeMeshNode>();
            Server->Nodes = NULL;
            m_socket = 0;
            m_port = 1;
        }
        
        //Adds a client
        bool addClient(Ptr<Node> node, int nodeNumber)
        {
            int i;
            if(Server->Nodes == NULL)
            {
                cout<<"Server\n";
                cout.flush();
                Server->Nodes = node;
                return true;
            }
            Ptr<treeMeshNode> newClient = CreateObject<treeMeshNode>();
            newClient->Nodes = node;
            newClient->index = nodeNumber;
            Ptr<treeMeshNode> traversalPointer = NULL;
            deque<Ptr<treeMeshNode> >remainingNodes;
            remainingNodes.push_back(Server);
            //breadth first search for next free node
            while(!remainingNodes.empty())
            {
                traversalPointer = remainingNodes.front();
                remainingNodes.pop_front();
                if(traversalPointer->connections.size() < MAX_CONNECTIONS)
                {
                    struct Connection connections;
                    connections.type = TREE;
                    connections.Node = newClient;
                    traversalPointer->connections.push_back(connections);
                    return true;
                }
                i = 0;
                while(i < traversalPointer->connections.size())
                {
                    remainingNodes.push_back(traversalPointer->connections[i].Node);
                    i++;
                }
            }
            return false;
        }
        
        //just for testing the breadth first traversal logic
        void bf_traversal()
        {
            int i = 0;
            Ptr<treeMeshNode> traversalPointer = NULL;
            deque<Ptr<treeMeshNode> > remainingNodes;
            remainingNodes.push_back(Server);
            while(!remainingNodes.empty())
            {
                traversalPointer = remainingNodes.front();
                remainingNodes.pop_front();
                cout<<traversalPointer->index<<"\n";
                i = 0;
                while(i < traversalPointer->connections.size())
                {
                    remainingNodes.push_back(traversalPointer->connections[i].Node);
                    i++;
                }
             }
        }

        void activateServer()
        {
            if(m_socket == 0)
            {
                //Bind any changes to m_socket to a call back function, like HandleRead and then chk for join and request
                //messages on that
                TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
                m_socket = Socket::CreateSocket(Server->Nodes,tid);
                InetSocketAddress local = InetSocketAddress(Ipv4Address::GetAny() , m_port);
                m_socket->Bind(local);
                if(addressUtils::IsMulticast(m_local))
                {
                    Ptr<UdpSocket> udpSocketx = DynamicCast<UdpSocket> (m_socket);
                    if(udpSocketx)
                    {
                        udpSocketx->MulticastJoinGroup(0,m_local);
                    }
                    else
                    {
                        cout<<"Error";
                    }
                }
            }
            m_socket->SetRecvCallback(MakeCallback(&tomoServer::HandleRead, this));
        }
            
        void HandleRead (Ptr<Socket> socket)
        {
            Ptr<Packet> packet;
            Address from;
            while (packet = socket->RecvFrom (from))
            {
                if (InetSocketAddress::IsMatchingType (from))
                {
                    NS_LOG_INFO ("Received " << packet->GetSize () << " bytes from " << InetSocketAddress::ConvertFrom (from).GetIpv4 ());
                    packet->RemoveAllPacketTags ();
                    packet->RemoveAllByteTags (); 
                    NS_LOG_LOGIC ("Echoing packet");
                    //socket->SendTo (packet, 0, from);
                }
            }
         }


        void deactivateServer()
        {
            //Remove the callback bindings on m_socket, actually equate the callback to a null callback
            if (m_socket != 0)
            {
                m_socket->Close ();
                m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
            }
        }

};

int main(int argc, char**argv)
{
    tomoServer Server;
    Ptr<Node> nodes = CreateObject<Node>();
    Ptr<Node> clientNode = CreateObject<Node>();
    int i = 0;
    //try adding 100 nodes all of which are one and the same
    while(i++ < 100)
        Server.addClient(nodes,rand());
    Server.bf_traversal();
    return 0;
}
