#include <iostream>
#include<string>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height;
};

int max(int a, int b) {
    return a > b ? a : b;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    newNode->height = 1;
    return newNode;
}

Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* temp = newRoot->left;
    
    newRoot->left = node;
    node->right = temp;

    newRoot->parent=node->parent;
    node->parent=newRoot;
    if(temp!=nullptr)temp->parent=node;
    
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* temp = newRoot->right;
    
    newRoot->right = node;
    node->left = temp;
    
    newRoot->parent=node->parent;
    node->parent=newRoot;
    if(temp!=nullptr)temp->parent=node;

    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

Node* insert(Node* root, int key) {
    if (root == nullptr){
        Node *temp=createNode(key);
        temp->parent=root;
        return temp;
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        // duplicate keys not allowed
        return root;
    }
    
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);
    
    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);
    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);
    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp; 
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr) return root;
    root->height = max(height(root->left), height(root->right)) + 1;
    
    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

Node* findUnbalancedRoot(Node* node) {
    while (node != nullptr) {
        if (abs(height(node->left) - height(node->right)) > 1)
            return node;
        node = node->parent;
    }
    return nullptr;
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

void printTree(Node* node, string indent, bool isRight) {
    if (node != nullptr) {
        printTree(node->right, indent + (!isRight ? "│   " : "    "), true);
        cout << indent;
        if (isRight) {
            cout << "┌──";//├ 195
        }
        else {
            cout << "└──";
        }
        cout << node->key << endl;

        printTree(node->left, indent + (isRight ? "│   " : "    "), false);
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 7);
    printTree(root, "", false);
    return 0;
}