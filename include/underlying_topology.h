// This file has the implementation of the underlyng topology. The classes defined here will allow user to specify number of
// nodes and type of channels connecting them. 
// Project : TOMO-Optima
// Authors : Shubhra Rana , shubhra199028@gmail.com
//           Revathi K , k.revathi1390@gmail.com
//           Sidhartha Mani, sidharthamani@me.com
// Licensing : Unlicensed
// Not for Commercial purpose

#ifndef TOMO_UNDERLYING_TOPOLOGY_H
#define TOMO_UNDERLYING_TOPOLOGY_H

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
using namespace ns3;

class topology {
  private:
    //
    //NS_LOG_COMPONENT_DEFINE("Topology_Generator");
    
    //
    NodeContainer sampleNodes;
    
    //
    CsmaHelper csma;
    
    //
    NetDeviceContainer CsmaDevices;
    
    //
    InternetStackHelper stack;

    //
    Ipv4AddressHelper address;
    
    //
    Ipv4InterfaceContainer csmaInterfaces;
  
  public:
    
    topology();

    topology(int n);
    
    // An example with one server and one client
    void EchoServerClient();
};

#endif
