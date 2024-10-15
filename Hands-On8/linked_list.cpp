#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};

class SinglyLinkedList {
public:
    Node* head;

    SinglyLinkedList() {
        head = nullptr;
    }

    Node* List_Search(int k) {
        Node* x = head;
        while (x != nullptr && x->key != k) {
            x = x->next;
        }
        return x;
    }

    void List_Insert(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
    }

    void List_Delete(int x) {
        Node* temp = head;
        Node* prev = nullptr;

        if (temp != nullptr && temp->key == x) {
            head = temp->next; 
            delete temp;        
            return;
        }

        while (temp != nullptr && temp->key != x) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) return;

        prev->next = temp->next;
        delete temp;
    }
};

int main() {
    SinglyLinkedList L;

    L.List_Insert(10);
    L.List_Insert(20);
    L.List_Insert(30);

    Node* found = L.List_Search(20);
    if (found != nullptr) {
        cout << "Found element: " << found->key << endl; 
    } else {
        cout << "Element not found" << endl;
    }

    L.List_Delete(20);
    found = L.List_Search(20);
    if (found == nullptr) {
        cout << "Element 20 successfully deleted" << endl;
    } else {
        cout << "Element 20 still present" << endl;
    }

    return 0;
}

/*
Output:

Found element: 20
Element 20 successfully deleted
*/