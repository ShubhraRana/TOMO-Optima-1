#include<iostream>
#include<vector>
#include<string>
using namespace std;

#define MAX_DEGREES 2

class Element {
public: 
  Ptr<Node> node_ptr;
  vector<Element*> connections;
};

class Tree {
  Element Server;
  int degrees;
  public:
    
    Tree() {
    }
    
    Tree(Ptr<Node> server) {
      Server.node_ptr = server;
      Server.degrees = 0;
   }

    void add_node(Ptr<Node> node) {
      Element New_Node;
      New_Node.node_ptr = node;
      if(Server.degrees < MAX_DEGREES) {
        Server.connections.push_back(New_Node);
        return;
      }
      
    }
};
