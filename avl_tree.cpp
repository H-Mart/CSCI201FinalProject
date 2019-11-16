#include <algorithm>
#include <iomanip>
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
    virtual int getKey() { std::cout << "This should never be called!"; }
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

    int balance() override { return 0; }

    int height() override { return 0; }

    bool hasValue() { return false; }

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

    int balance() override { return left->height() - right->height(); }

    int height() override { return h; }

    int getKey() override { return key; }

    bool hasValue() { return true; }

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
    int bal = root->balance();  // - = right-heavy, + = left heavy

    if (bal < -1) {                         // tree is right-heavy
        if (key < root->right->getKey()) {  // Key was inserted to the right of
                                            // the right child
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }

    if (bal > 1) {                         // tree is left-heavy
        if (key > root->left->getKey()) {  // Key was inserted to the right of
                                           // the left child
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }

    return root;
}

INode* searchTree(INode* root, int value) {
    INode** searchPointer = &root;
    while (1) {
        if ((*searchPointer)->getKey() == value) {
            return *searchPointer;
        }
        if (value < (*searchPointer)->getKey()) {
            if (root->left->hasValue()) {
                *searchPointer = root->left;
            } else {
                return new EmptyNode;
            }
        }
        if (value > (*searchPointer)->getKey()) {
            if (root->right->hasValue()) {
                *searchPointer = root->right;
            } else {
                return new EmptyNode;
            }
        }
    }
}

class AvlTree {
   private:
    INode* root;

    void postorder(INode* p, int indent = 0) {
        if (p->hasValue()) {
            if (p->right->hasValue()) {
                postorder(p->right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right->hasValue()) std::cout << " /\n"
                                                << std::setw(indent) << ' ';
            std::cout << p->getKey() << "\n ";
            if (p->left->hasValue()) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                postorder(p->left, indent + 4);
            }
        }
    }

   public:
    AvlTree() { root = new EmptyNode(); }
    void insert(int key) { root = insertNode(root, key); }
    INode* search(int key) { return searchTree(root, key); }
    int height() { return root->height(); }
    void postorder(int indent = 4) {
        postorder(root);
    }
};

int main() {
    return 0;
}