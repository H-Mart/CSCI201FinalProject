#include <algorithm>
#include <iostream>
#include <random>

class INode {
   protected:
    int h;
    int key;

   public:
    INode* left;
    INode* right;
    virtual int balance() = 0;
    virtual int height() = 0;
    virtual int getKey() {}
    virtual bool hasValue() = 0;
    virtual void recalcHeight() = 0;
};

class EmptyNode : public INode {
   public:
    EmptyNode() {
        this->h = 0;
        this->left = NULL;
        this->right = NULL;
    }

    int balance() override {
        return 0;
    }

    int height() override {
        return 0;
    }

    bool hasValue() {
        return false;
    }

    void recalcHeight() override { return; }
};

class Node : public INode {
   public:
    Node(int key) {
        this->h = 1;
        this->left = new EmptyNode();
        this->right = new EmptyNode();
        this->key = key;
    }

    int balance() override {
        return left->height() - right->height();
    }

    int height() override {
        return h;
    }

    int getKey() override {
        return key;
    }

    bool hasValue() {
        return true;
    }

    void recalcHeight() override {
        h = std::max(left->height(), right->height()) + 1;
    }
};

INode* rotateRight(INode* root) {
    // assuming the root is not null
    INode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->recalcHeight();
    newRoot->recalcHeight();

    return newRoot;
}

INode* rotateLeft(INode* root) {
    // assuming the root is not null
    INode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root->recalcHeight();
    newRoot->recalcHeight();

    return newRoot;
}

void treeWalk(INode* root, int lvl = 0) {
    if (!root->right->hasValue()) {
        treeWalk(root->right, lvl + 1);
    }
    if (!root->left->hasValue()) {
        treeWalk(root->left, lvl + 1);
    }
    std::cout << root->getKey() << " " << lvl << " | " << std::endl;
}

int treeLength(INode* root) {
    if (!root->hasValue()) {
        return 0;
    }
    return treeLength(root->right) + treeLength(root->left) + 1;
}

INode* insertNode(INode* root, int key) {
    if (!root->hasValue()) {
        return new Node(key);
    } else if (key < root->getKey()) {
        root->left = insertNode(root->left, key);
    } else if (key > root->getKey()) {
        root->right = insertNode(root->right, key);
    } else {
        return root;
    }

    root->recalcHeight();

    int bal = root->balance();  // - = left-heavy, + = right heavy

    if (bal > 1 && key > root->right->getKey()) {  // tree is right-heavy and the key was inserted to the right of the right child - Right-Right
        return rotateLeft(root);
    }

    if (bal < -1 && key < root->left->getKey()) {  // tree is left-heavy and the key was inserted to the Left of the Left child - Left-Left
        return rotateRight(root);
    }

    if (bal > 1 && key < root->right->getKey()) {  // tree is right-heavy and the key was inserted to the Left of the Right child - Right-Left
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if (bal < -1 && key > root->left->getKey()) {  // tree is left-heavy and the key was inserted to the Left of the Right child - Left-Right
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    return root;
}

class AvlTree {
   private:
    INode* root;

   public:
    // void insert() {
    // root = insertNode(root, )
    // }
};

int main() {
    std::random_device rd;
    std::mt19937_64 gen(rd());

    /* This is where you define the number generator for unsigned long long: */
    std::uniform_int_distribution<int> dis;

    INode* root = new EmptyNode();
    // std::cout << root->getKey() << std::endl;
    for (int i = 0; i < 300; i++) {
        root = insertNode(root, i);
        std::cout << fstd::endl;
    }

    // treeWalk(root);

    return 0;
}