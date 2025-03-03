#include <iostream>
#include "../Code/RBTRee/RBTree.hpp"
using namespace std;

class A{
public:
    A(){
        cout<<"A"<<endl;
    }
    virtual void donothing(){
        cout<<"donothing"<<endl;
    }
    ~A(){
        cout<<"~A"<<endl;
    }
};
class C:public A{
public:
    C(){
        cout<<"C"<<endl;
        a=1;
    }
    int a;
    ~C(){
        cout<<"~C"<<endl;
    }
};

int main()
{
    // cout<<"Hello World!"<<endl;
    // RBTree<int> tree;
    // tree.Insert(1);
    // tree.Insert(5);
    // tree.Insert(0);
    // tree.Insert(3);
    // tree.Insert(-1);
    // tree.Display(); 
    // tree.DisplayData(); 
    A *d=new C();
    d->donothing();
    delete d;
    system("pause");
    return 0;
}