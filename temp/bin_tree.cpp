
class node_tree
{
private :
 int value;
 node_tree* left;
 node_tree* right;
 node_tree* peer;

public :

node_tree(int n)
{
value=n;
left=NULL;
right=NULL;
peer=NULL;
}
  void add(int val,node_tree root){
  node_tree xc;
  //check for degree
  if(root.left==NULL)
  {
   xc.set(val);
   root.left=&xc;
   xc.left=xc.right=NULL;
  }
  else if (root.right==NULL)
  //add to the right tree
  {
  xc.set(val);
  root.right=&xc;
  root.left.peer=xc;
  xc.peer=NULL;
  }
}
void display(node_tree root)
{
while(root->
}
void main()
{
node_tree root(3);

root.add(4);
root.add(7);
display(root);
}
