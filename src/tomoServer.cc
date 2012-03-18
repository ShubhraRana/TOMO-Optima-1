#include<iostream>
#include<cstdlib>
#include<ns3/core-module.h>
#include<ns3/internet-module.h>
#include<ns3/network-module.h>
#include<deque>
using namespace std;
using namespace ns3;

#define TREE 0
#define MESH 1
#define MAX_CONNECTIONS 2

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

//The server Implementation
class tomoServer
{
    private:
        Ptr<treeMeshNode> Server;
    public:
        tomoServer()
        {
            Server = CreateObject<treeMeshNode>();
            Server->Nodes = NULL;
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
