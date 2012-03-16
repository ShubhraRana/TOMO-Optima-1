#include<iostream>
using namespace std;

class tree;

class node 
{
int value;
node *left,*right,*peer;
public:
node()
{
  left = NULL;
  right = NULL;
  peer = NULL;
}
};

class tree
{
node *root;
public:
tree()
{
  root = NULL;
}

node* go_to_node(node *x, int flag)
{
  if(x == NULL)
    return x;
  if(flag == 0)
   return x;
  x = go_to_node(x->left,1);
 
}

void add_node(int val)
{
  if(root == NULL)
  {
    root = new node();
    root->value = val;
    return; 
  }
  // if root is not empty
  node *temp = go_to_node(root,1);
 
}

};
