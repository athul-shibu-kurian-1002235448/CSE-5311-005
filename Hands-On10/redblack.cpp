#include <iostream>
#include <string>
using namespace std;

enum Color {RED, BLACK};

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = NULL;
        color = RED;
    }
};

class RedBlackTree {
public:
    Node* root;
    Node* TNULL;

    void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->parent = parent;
        node->left = node->right = NULL;
        node->color = BLACK;
    }

    void preOrderHelper(Node* node);
    void inOrderHelper(Node* node);
    void postOrderHelper(Node* node);

    Node* searchTreeHelper(Node* node, int key);

    void fixInsert(Node* k);
    void fixDelete(Node* x);

    void rbTransplant(Node* u, Node* v);
    void deleteNodeHelper(Node* node, int key);

    void leftRotate(Node* x);
    void rightRotate(Node* x);

    void printHelper(Node* root, string indent, bool last);

    RedBlackTree();
    void preorder();
    void inorder();
    void postorder();

    Node* searchTree(int k);
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    Node* successor(Node* x);
    Node* predecessor(Node* x);

    void insert(int key);
    void deleteNode(int data);
    void printTree();

    Node* getRoot() {
        return this->root;
    }
};

RedBlackTree::RedBlackTree() {
    TNULL = new Node(0);
    TNULL->color = BLACK;
    TNULL->left = TNULL->right = TNULL;
    root = TNULL;
}

void RedBlackTree::preOrderHelper(Node* node) {
    if (node != TNULL) {
        cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    } 
}

void RedBlackTree::inOrderHelper(Node* node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    } 
}

void RedBlackTree::postOrderHelper(Node* node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->data << " ";
    } 
}

void RedBlackTree::preorder() {
    preOrderHelper(this->root);
}

void RedBlackTree::inorder() {
    inOrderHelper(this->root);
}

void RedBlackTree::postorder() {
    postOrderHelper(this->root);
}

Node* RedBlackTree::searchTreeHelper(Node* node, int key) {
    if (node == TNULL || key == node->data) {
        return node;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    } 
    return searchTreeHelper(node->right, key);
}

Node* RedBlackTree::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->left){
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        this->root = y;
    } else if (x == x->parent->right){
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int key) {
    Node* node = new Node(key);
    node->parent = NULL;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED; // New node must be red

    Node* y = NULL;
    Node* x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    // if new node is root, simply return
    if (node->parent == NULL){
        node->color = BLACK;
        return;
    }

    // if the grandparent is null, simply return
    if (node->parent->parent == NULL) {
        return;
    }

    // Fix the tree
    fixInsert(node);
}

void RedBlackTree::fixInsert(Node* k) {
    Node* u;
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == RED) {
                // case 3.1
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;	
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // case 3.2.1
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if (u->color == RED) {
                // mirror case 3.1
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;	
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // mirror case 3.2.1
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

Node* RedBlackTree::maximum(Node* node) {
    while (node->right != TNULL) {
        node = node->right;
    }
    return node;
}

void RedBlackTree::rbTransplant(Node* u, Node* v){
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::deleteNode(int data) {
    deleteNodeHelper(this->root, data);
}

void RedBlackTree::deleteNodeHelper(Node* node, int key) {
    // find the node containing key
    Node* z = TNULL;
    Node* x, *y;
    while (node != TNULL){
        if (node->data == key) {
            z = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        cout << "Cannot find key in the tree" << endl;
        return;
    }

    y = z;
    Color y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK){
        fixDelete(x);
    }
}

void RedBlackTree::fixDelete(Node* x) {
    Node* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                // case 3.1
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                // case 3.2
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    // case 3.3
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                } 

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == RED) {
                // case 3.1
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                // case 3.2
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    // case 3.3
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                } 

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        } 
    }
    x->color = BLACK;
}

void RedBlackTree::printHelper(Node* root, string indent, bool last) {
    // print the tree structure on the screen
    if (root != TNULL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }

        string sColor = root->color == RED?"RED":"BLACK";
        cout << root->data << "(" << sColor << ")" << endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

void RedBlackTree::printTree() {
    if (root) {
        printHelper(this->root, "", true);
    }
}

int main() {
    RedBlackTree bst;

    // Insert elements
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(57);

    cout << "Red-Black Tree after insertion:" << endl;
    bst.printTree();
    cout << endl;

    // Search for an element
    cout << "Searching for 40 in the tree:" << endl;
    Node* node = bst.searchTree(40);
    if (node != bst.TNULL) {
        cout << "Found node with key " << node->data << endl;
    } else {
        cout << "Node not found" << endl;
    }
    cout << endl;

    // Delete an element
    cout << "Deleting node 40" << endl;
    bst.deleteNode(40);

    cout << "Red-Black Tree after deletion:" << endl;
    bst.printTree();
    cout << endl;

    // Traversal
    cout << "Inorder traversal after deletion: ";
    bst.inorder();
    cout << endl;

    return 0;
}
