// This file has the implementation of the underlyng topology. The classes defined here will allow user to specify number of
// nodes and type of channels connecting them. 
// Project : TOMO-Optima
// Authors : Shubhra Rana , shubhra199028@gmail.com
//           Revathi K , k.revathi1390@gmail.com
//           Sidhartha Mani, sidharthamani@me.com
// Licensing : Unlicensed
// Not for Commercial purpose

#include "underlying_topology.h"

using namespace ns3;

topology::topology() {
  sampleNodes.Create(3);
  CsmaDevices = csma.Install(sampleNodes);
  stack.Install(sampleNodes);
  address.SetBase("10.1.1.0","255.255.255.0");
  csmaInterfaces = address.Assign(CsmaDevices);
}

topology::topology(int n) {
  sampleNodes.Create(n);
  CsmaDevices = csma.Install(sampleNodes);
  stack.Install(sampleNodes);
  address.SetBase("10.1.1.0","255.255.255.0");
  csmaInterfaces = address.Assign(CsmaDevices);
}

void topology::EchoServerClient() {
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  UdpEchoServerHelper echoServer (9);
  ApplicationContainer serverApps = echoServer.Install (sampleNodes.Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (0), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (4));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (256));

  ApplicationContainer clientApps = echoClient.Install (sampleNodes.Get (1));
  clientApps.Start (Seconds (1.0));
  clientApps.Stop (Seconds (10.0));
  csma.EnablePcapAll("trace/Example",true);
  Simulator::Run();
  Simulator::Destroy();
}
