#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
private:
    int height(Node* N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int getBalance(Node* N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    Node* insert(Node* node, int key) {
        // 1. Perform the normal BST insertion
        if (node == NULL) {
            Node* newNode = new Node();
            newNode->key = key;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;
            return newNode;
        }

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        // 2. Update height
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Get balance factor
        int balance = getBalance(node);

        // 4. Balance the node
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int key) {
        // Perform standard BST delete
        if (root == NULL)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);

        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        else {
            if ((root->left == NULL) || (root->right == NULL)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;

                delete temp;
            } else {
                Node* temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == NULL)
            return root;

        // Update height
        root->height = 1 + max(height(root->left), height(root->right));

        // Balance the node
        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    Node* search(Node* root, int key) {
        if (root == NULL || root->key == key)
            return root;

        if (key < root->key)
            return search(root->left, key);

        return search(root->right, key);
    }

    void preOrder(Node* root) {
        if (root != NULL) {
            cout << root->key << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

public:
    Node* root;
    AVLTree() { root = NULL; }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        return search(root, key) != NULL;
    }

    void preOrder() {
        preOrder(root);
    }
};

int main() {
    AVLTree tree;

    // Insertion
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Preorder traversal after insertions: ";
    tree.preOrder();
    cout << endl;

    // Query/Search
    int key = 20;
    if (tree.search(key))
        cout << "Element " << key << " found in the AVL tree." << endl;
    else
        cout << "Element " << key << " not found in the AVL tree." << endl;

    // Deletion
    tree.deleteKey(30);

    cout << "Preorder traversal after deletion of 30: ";
    tree.preOrder();
    cout << endl;

    return 0;
}
