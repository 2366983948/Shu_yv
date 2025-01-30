#ifndef _RBTREE_HPP_
#define _RBTREE_HPP_
 
#include <iostream>
using namespace std;

enum Color  // 1 is red，0 is black node
{
    Black = 0, 
    Red
};

template<typename T> 
class RBTreeNode
{
public :
    T data;
    Color color; // 1 代表红色， 0 代表黑色
    RBTreeNode* father;  // 父节点
    RBTreeNode* left;    // 左孩子
    RBTreeNode* right;   // 右孩子

    RBTreeNode(): color(Red), father(nullptr), left(nullptr), right(nullptr){}; 
    RBTreeNode(T _data): data(_data), color(Red) , father(nullptr), left(nullptr), right(nullptr){};
    ~RBTreeNode(){ };
};

//红黑树的实现
 
template<typename T>
class RBTree
{
public:
    RBTree();
    ~RBTree();
    bool Insert(T data);    // 插入节点
    void Display();
    void DisplayData();
private:
    RBTreeNode<T>* treeRoot;
    RBTreeNode<T>* SearchNode(T data);        //有就返回，没有就返回null
    RBTreeNode<T>* FindParent(T data);       // 有就返回，没有就返回父节点
    void AdjustNode(RBTreeNode<T>* curNode);    // 调整节点
    void FreeNode(RBTreeNode<T>* curNode);
    bool Rotate(RBTreeNode<T>* curNode,bool isleft); //旋转
    bool RightRotate(RBTreeNode<T>* curNode); // 右旋
    bool LeftRotate(RBTreeNode<T>* curNode); // 左旋

    void Output(RBTreeNode<T>* curNode, bool left, string const& indent); // 可视化红黑树
    void ViewTree(RBTreeNode<T>* curNode);          //按顺序返回数据
    void ViewTreeByGraphic(RBTreeNode<T>* curNode); // 可视化红黑树
};

template <typename T>
inline RBTreeNode<T> *RBTree<T>::SearchNode(T data)
{
    RBTreeNode<T>* tmpRoot = treeRoot;
    while(tmpRoot != nullptr)
    {
        if(data < tmpRoot->data) { tmpRoot = tmpRoot->left; }
        else if(data > tmpRoot->data) { tmpRoot = tmpRoot->right; }
        else return tmpRoot;
    } 
    return nullptr;
}

template <typename T>
void RBTree<T>::FreeNode(RBTreeNode<T> *curNode)
{
    if(curNode == nullptr) return ;
    if(curNode->right) FreeNode(curNode->right);
    if(curNode->left)  FreeNode(curNode->left);
 
    delete curNode;
    curNode = nullptr;
}

template <typename T>
inline bool RBTree<T>::Rotate(RBTreeNode<T> *curNode, bool isleft)
{
    RBTreeNode<T>* curNodeLeft = curNode->left;
    RBTreeNode<T>* curNodeRight = curNode->right;
    RBTreeNode<T>* curNodeFather = curNode->father;
    
    // 操作1 ：当前节点下降
    if(isleft){
        curNode->right = curNodeRight->left;
        if(curNode->right != nullptr) curNode->right->father = curNode;
    }else{
        curNode->left = curNodeLeft->right;
        if(curNode->left != nullptr) curNode->left->father = curNode;  // 回指
    }
    // 操作2 ：孩子节点上升
    if(isleft){
        curNodeRight->left = curNode;
        curNode->father = curNodeRight;
    }else{
        curNodeLeft->right = curNode;
        curNode->father = curNodeLeft;
    }
    // 操作3 ：与父节点连接
    RBTreeNode<T>* t=isleft?curNodeRight:curNodeLeft;
    t->father = curNodeFather;
    if(curNodeFather == nullptr)treeRoot = t; // 这里需要注意，需要把根节点更新
    else if(curNodeFather->left == curNode)curNodeFather->left = t;
    else curNodeFather->right = t;
    return true;
}

template<typename T>
bool RBTree<T>::Insert(T data)
{
    if(treeRoot == nullptr) // 1.       红黑树为空树的情况，将节点作为根节点，并且设置为黑色
    {
        treeRoot = new RBTreeNode<T>(data);
        treeRoot->color = Black;
        return true;
    }
 
    RBTreeNode<T>* tmpTreeRoot = FindParent(data);     //父节点
    RBTreeNode<T>* curNode = new RBTreeNode<T>(data); // 当前需要插入的节点

    if(tmpTreeRoot == nullptr || tmpTreeRoot->data==data)return false;
    // 2.插入节点
    if(curNode->data < tmpTreeRoot->data) // 在当前节点的左边
    {
        tmpTreeRoot->left = curNode;
        curNode->father = tmpTreeRoot;
    }
    else if(curNode->data > tmpTreeRoot->data)
    {
        tmpTreeRoot->right = curNode;
        curNode->father = tmpTreeRoot;
    }
    // 3. 如果父节点为黑色，不用调整
    if(tmpTreeRoot->color == Black) return true; 
 
    // 4. 插入节点的父节点为红色，需要修复
    AdjustNode(curNode);
    return true;
}
 
template<typename T>
bool RBTree<T>::RightRotate(RBTreeNode<T>* curNode)
{
    Rotate(curNode,false);
    return 1;
}
 
template<typename T>
bool RBTree<T>::LeftRotate(RBTreeNode<T>* curNode)
{
    Rotate(curNode,true);
    return true;
}
 
template<typename T>
RBTreeNode<T>* RBTree<T>::FindParent(T data)
{
    RBTreeNode<T>* tmpRoot = treeRoot;
    while(tmpRoot != nullptr)
    {
        if(data < tmpRoot->data) // 往左
        {
            if(tmpRoot->left != nullptr) tmpRoot = tmpRoot->left;
            else return tmpRoot;
        }
        else if(data > tmpRoot->data) // 往右
        {
            if(tmpRoot->right != nullptr) tmpRoot = tmpRoot->right;
            else return tmpRoot;
        }
        else // 找到了
        {
            return tmpRoot;
        }
    } 
    return nullptr;
}

template <typename T>
inline void RBTree<T>::AdjustNode(RBTreeNode<T> *curNode)
{
    RBTreeNode<T>* uncleNode = nullptr;
    while(  curNode->father != nullptr && // 当前节点不是根节点
            curNode->father->father != nullptr && // 当前节点有爷爷节点
            curNode->father->color == Red) // 当前节点的父节点是红色节点
    {
            //        grandfather
            //            / \ 
            //           /   \ 
            //      father    ?(4.1)
            //        / \ 
            //(4.2.1)?   ?(4.2.2)
        RBTreeNode<T>* fatherNode = curNode->father;
        RBTreeNode<T>* grandFatherNode = fatherNode->father;
 
        if(fatherNode == grandFatherNode->left) // 4.2.1 父节点为左子树
        {
            uncleNode = grandFatherNode->right;
            if(uncleNode != nullptr && uncleNode->color == Red) // 4.1 叔叔节点存在且为红色
            {
                fatherNode->color = Black;
                uncleNode->color = Black;
                if(grandFatherNode->father != nullptr) grandFatherNode->color = Red; // 如果为空那么该节点是父节点，不能是红色
                curNode = grandFatherNode;
            }
            else  // 4.2 叔叔节点为空节点或者为黑色节点
            {
                if(curNode == fatherNode->left) // 4.2.1.1 当前节点在父节点的左边，LL(双红的情况)
                // 1. 将父节点设置为黑色，将爷爷节点设置为红色
                // 2. 对爷爷节点进行右旋
                {
                    fatherNode->color = Black;
                    grandFatherNode->color = Red;
                    RightRotate(grandFatherNode); // 右旋
                }
                else if(curNode == fatherNode->right) // 4.2.1.2 当前节点的父节点的右边，LR双红
                {
                    curNode = curNode->father;
                    LeftRotate(curNode);
                }
            }
        }
                //        grandfather
                //            / \ 
                //           /   \ 
                //      ?(4.1)   father
                //                / \ 
                //        (4.2.1)?   ?(4.2.2)
        else // 4.2.2 父节点为右子树
        {
            uncleNode = grandFatherNode->left;
            if(uncleNode != nullptr && uncleNode->color == Red) 
                // 4.1 叔叔节点存在，且为红色。
                // 叔叔节点的判断位置有些乱，是因为理论要先能找到叔叔节点，
                // 所以需要先进行4.2.1/2节的判断，也就是插入节点的父节点是爷爷节点的左孩子还是右孩子
            {
                fatherNode->color = Black;
                uncleNode->color = Black;
                if(grandFatherNode->father != nullptr) grandFatherNode->color = Red;
                curNode = grandFatherNode;
            }
            else
            {
                if(curNode == fatherNode->right) // 4.2.2.1 RR 双红
                {
                    fatherNode->color = Black;
                    grandFatherNode->color = Red;
                    LeftRotate(grandFatherNode);
                }
                else if(curNode == fatherNode->left)// 4.2.2.2 RL双红
                {
                    curNode = curNode->father;
                    RightRotate(curNode);
                }
            }
        }
    }
}

template <typename T>
inline void RBTree<T>::Display()
{
    ViewTreeByGraphic(treeRoot);
}

template <typename T>
inline void RBTree<T>::DisplayData()
{
    ViewTree(treeRoot);
}

template<typename T>
void RBTree<T>::ViewTree(RBTreeNode<T>* curNode) // 线序遍历打印红色树查看正确性
{
    if(curNode->left != nullptr) ViewTree(curNode->left);
    cout << curNode->data << ' ';
    if(curNode->right != nullptr) ViewTree(curNode->right);
}
 
template<typename T>
void RBTree<T>::Output(RBTreeNode<T>* curNode, bool left, string const& indent)
{
    if (curNode->right)
    {
        Output(curNode->right, false, indent + (left ? "|      " : "       "));
    }
    cout << indent;
    cout << (left ? '\\' : '/');
    cout << "-----";
    cout << curNode->data << "(" << (curNode->color == Red ? 'R' : 'B') << ")" << '\n';
    if(curNode->left)
    {
        Output(curNode->left, true, indent + (left ? "       " : "|      "));
    }
    
}
 
template<typename T>
void RBTree<T>::ViewTreeByGraphic(RBTreeNode<T>* curNode)
{
    cout << "\n\n-------------------- Red Black Tree ------------------------";
    cout << "\n--------------- B : Black Node R : Red Node -------------------\n\n\n";
    if(curNode->right)
    {
        Output(curNode->right, false, "");
    }
    cout << curNode->data <<  "(" << (curNode->color == Red ? 'R' : 'B') << ")" <<  '\n';
    if(curNode->left)
    {
        Output(curNode->left, true, "");
    }
    cout << "\n\n------------------------------------------------------------\n";
}

template<typename T>
RBTree<T>::RBTree() : treeRoot(nullptr)
{
 
}
 
template<typename T>
RBTree<T>::~RBTree()
{
    FreeNode(treeRoot);
}

#endif