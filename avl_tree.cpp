#include <algorithm>
#include <iostream>

class Node {
    public:
    int height;
    Node* left;
    Node* right;
    int key;

    Node(int key) {
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
        this->key = key;
    }
};

int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->right) - getHeight(node->left);
}

Node* rotateRight(Node* root) {
    // assuming the root is not null
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* rotateLeft(Node* root) {
    // assuming the root is not null
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

void treeWalk(Node* root, int lvl) {
    if (root->right != NULL) {
        treeWalk(root->right, lvl + 1);
    }
    if (root->left != NULL) {
        treeWalk(root->left, lvl + 1);
    }
    std::cout << root->key << " " << lvl << " | " << std::endl;
}

int treeLength(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return treeLength(root->right) + treeLength(root->left) + 1;
}

Node* insertNode(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    } else if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    } else {
        return root;
    }

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

    int bal = getBalance(root);  // - = left-heavy, + = right heavy

    if (bal > 1 && key > root->right->key) {  // tree is right-heavy and the key was inserted to the right of the right child - Right-Right
        return rotateLeft(root);
    }

    if (bal < -1 && key < root->left->key) {  // tree is left-heavy and the key was inserted to the Left of the Left child - Left-Left
        return rotateRight(root);
    }

    if (bal > 1 && key < root->right->key) {  // tree is right-heavy and the key was inserted to the Left of the Right child - Right-Left
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if (bal < -1 && key > root->left->key) {  // tree is left-heavy and the key was inserted to the Left of the Right child - Left-Right
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    return root;
}

class AvlTree {
   private:
    Node* root;

   public:
   // todo
    // void insert() {
        // root = insertNode(root, )
    // }
};

int main() {
    return 0;
}