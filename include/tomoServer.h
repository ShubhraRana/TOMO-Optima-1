//Decription
// nodes and type of channels connecting them. 
// Project : TOMO-Optima
// Authors : Shubhra Rana , shubhra199028@gmail.com
//           Revathi K , k.revathi1390@gmail.com
//           Sidhartha Mani, sidharthamani@me.com
// Licensing : Unlicensed
// Not for Commercial purpose

#ifndef TOMO_TOMOSERVER_H
#define TOMO_TOMOSERVER_H

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
using namespace ns3;


class tomoServer : public udpServer {
  public:
    
  private:
    sendData(void *params);
};

#endif
