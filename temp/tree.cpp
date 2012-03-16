#include <math.h>
#include<iostream>
using namespace std;
//int level[20]={0};
class element
{
private : int val;
         // bin_tree* left;
        //  bin_tree* right;
          
public :
      void set(int num)
        {
        val=num;
        }

     int get(){
     return(val);
    }

}nodes[100];

void display(int n){
        cout<<"\n";
        int d=1;
        for(int i=0;i<n;i++)
        {
           if((i+1)==pow(2,d))
           { cout<<"\n";d+=1;}
           cout<<nodes[i].get()<<"\t";
           
        }
       }
 main()
{
int i;
for(i=0;i<100;i++)
nodes[i].set(-5);

//creation of nodes
int n,num;
cout<<"Enter the number of nodes in the tree: ";
cin>>n;
for(i=0;i<n;i++)
{
 cout<<"enter the value of "<<i+1<<" node:";
 cin>>num;
 nodes[i].set(num);
}
display(n);
}
