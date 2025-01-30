
#include<iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    TreeNode* root;
    int getHeight(TreeNode* node);
    int getBalanceFactor(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* insertNode(TreeNode* node, int value);
    TreeNode* deleteNode(TreeNode* node, int value);
    TreeNode* findMin(TreeNode* node);
    int calculateHeight(TreeNode* node);
public:
    AVLTree();
    void insert(int value);
    void remove(int value);
    void display();
};

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

TreeNode* AVLTree::rotateLeft(TreeNode* node) {
    TreeNode* rightChild = node->right;
    TreeNode* leftOfRightChild = rightChild->left;

    rightChild->left = node;
    node->right = leftOfRightChild;

    node->height = calculateHeight(node);
    rightChild->height = calculateHeight(rightChild);

    return rightChild;
}

TreeNode* AVLTree::rotateRight(TreeNode* node) {
    TreeNode* leftChild = node->left;
    TreeNode* rightOfLeftChild = leftChild->right;

    leftChild->right = node;
    node->left = rightOfLeftChild;

    node->height = calculateHeight(node);
    leftChild->height = calculateHeight(leftChild);

    return leftChild;
}

TreeNode* AVLTree::insertNode(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    if (value < node->data) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->data) {
        node->right = insertNode(node->right, value);
    }
    else {
        return node; // value already exists
    }

    node->height = calculateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && value < node->left->data) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && value > node->right->data) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

TreeNode* AVLTree::findMin(TreeNode* node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}

int AVLTree::calculateHeight(TreeNode* node) {
    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

void AVLTree::insert(int value) {
    root = insertNode(root, value);
}

void AVLTree::remove(int value) {
    root = deleteNode(root, value);
}

TreeNode* AVLTree::deleteNode(TreeNode* node, int value) {
    if (node == nullptr) {
        return node;
    }

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            TreeNode* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            TreeNode* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = calculateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void printTree(TreeNode* node, string indent, bool isRight) {
    if (node != nullptr) {
        printTree(node->right, indent + (!isRight ? "│   " : "    "), true);
        cout << indent;
        if (isRight) {
            cout << "┌──";//├ 195
        }
        else {
            cout << "└──";
        }
        cout << node->data << endl;

        printTree(node->left, indent + (isRight ? "│   " : "    "), false);
    }
}

void AVLTree::display() {
    printTree(root, "", false);
}

int main() {
    AVLTree tree;

    // 测试插入
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // 展示树结构
    tree.display();
    cout<<endl;
    // 测试删除节点
    tree.remove(30);

    // 展示删除节点后的树结构
    tree.display();

    return 0;
}
/*

以上代码实现了一个基本的平衡二叉树类。它包括节点类(`TreeNode`)和平衡二叉树类(`AVLTree`)。
`AVLTree`类提供了插入(`insert`)、删除(`remove`)和展示(`display`)方法来操作和展示平衡二叉树。
在主函数中，我们演示了如何使用平衡二叉树类来插入节点、删除节点并展示树的结构。

*/