#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = newNode(data);
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == nullptr || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* findMin(Node* node) {
    while (node && node->left != nullptr)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Inorder traversal of the given tree: ";
    inorder(root);
    cout << endl;

    int key = 40;
    if (search(root, key))
        cout << "Key " << key << " found in the tree." << endl;
    else
        cout << "Key " << key << " not found in the tree." << endl;

    key = 100;
    if (search(root, key))
        cout << "Key " << key << " found in the tree." << endl;
    else
        cout << "Key " << key << " not found in the tree." << endl;

    root = deleteNode(root, 20);
    cout << "Inorder traversal after deleting 20: ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, 30);
    cout << "Inorder traversal after deleting 30: ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, 50);
    cout << "Inorder traversal after deleting 50: ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, 100);
    cout << "Inorder traversal after attempting to delete 100 (non-existing key): ";
    inorder(root);
    cout << endl;

    return 0;
}
