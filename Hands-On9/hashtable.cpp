#include <iostream>
using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), value(v), prev(NULL), next(NULL) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(NULL), tail(NULL) {}
    ~DoublyLinkedList() {
        clear();
    }

    void insert(int key, int value) {
        Node* newNode = new Node(key, value);
        if (!head) {
            head = tail = newNode;
        } else {
            // Insert at the front
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    bool deleteNode(int key) {
        Node* curr = head;
        while (curr) {
            if (curr->key == key) {
                if (curr->prev)
                    curr->prev->next = curr->next;
                else
                    head = curr->next;

                if (curr->next)
                    curr->next->prev = curr->prev;
                else
                    tail = curr->prev;

                delete curr;
                return true;
            }
            curr = curr->next;
        }
        return false; // key not found
    }

    Node* search(int key) {
        Node* curr = head;
        while (curr) {
            if (curr->key == key) {
                return curr;
            }
            curr = curr->next;
        }
        return NULL; // key not found
    }

    void clear() {
        Node* curr = head;
        while (curr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        head = tail = NULL;
    }
};

unsigned int defaultHashFunc(int key, int capacity) {
    //using both multiplication and division
    unsigned int hash = key * 31;
    return hash % capacity;
}

class HashTable {
private:
    DoublyLinkedList** table; // array of pointers to DoublyLinkedList
    int capacity; // size of the table array
    int size;     // number of elements stored
    unsigned int (*hashFunc)(int key, int capacity);

    void resize(int newCapacity) {
        // Create new table
        DoublyLinkedList** newTable = new DoublyLinkedList*[newCapacity];
        for (int i = 0; i < newCapacity; ++i) {
            newTable[i] = new DoublyLinkedList();
        }

        // Rehash all elements
        for (int i = 0; i < capacity; ++i) {
            Node* curr = table[i]->head;
            while (curr) {
                int key = curr->key;
                int value = curr->value;
                unsigned int hash = hashFunc(key, newCapacity);
                newTable[hash]->insert(key, value);
                curr = curr->next;
            }
            delete table[i];
        }
        delete[] table;

        // Update table and capacity
        table = newTable;
        capacity = newCapacity;
    }

public:
    HashTable(int cap = 8, unsigned int (*hashFunc)(int key, int capacity) = defaultHashFunc) {
        capacity = cap;
        size = 0;
        this->hashFunc = hashFunc ? hashFunc : defaultHashFunc;
        table = new DoublyLinkedList*[capacity];
        for (int i = 0; i < capacity; ++i) {
            table[i] = new DoublyLinkedList();
        }
    }

    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            delete table[i];
        }
        delete[] table;
    }

    void insert(int key, int value) {
        // Check if key already exists, update value if it does
        int index = hashFunc(key, capacity);
        Node* node = table[index]->search(key);
        if (node) {
            node->value = value;
            return;
        }

        table[index]->insert(key, value);
        ++size;

        // Check if resizing is needed
        if (size >= capacity) {
            resize(capacity * 2);
        }
    }

    bool deleteKey(int key) {
        int index = hashFunc(key, capacity);
        bool result = table[index]->deleteNode(key);
        if (result) {
            --size;
            // Check if resizing is needed
            if (capacity > 8 && size <= capacity / 4) {
                resize(capacity / 2);
            }
        }
        return result;
    }

    bool search(int key, int& value) {
        int index = hashFunc(key, capacity);
        Node* node = table[index]->search(key);
        if (node) {
            value = node->value;
            return true;
        } else {
            return false;
        }
    }
};

// Example usage
int main() {
    HashTable ht;

    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);

    int value;
    if (ht.search(2, value)) {
        cout << "Key 2 has value " << value << endl;
    } else {
        cout << "Key 2 not found" << endl;
    }

    ht.deleteKey(2);

    if (ht.search(2, value)) {
        cout << "Key 2 has value " << value << endl;
    } else {
        cout << "Key 2 not found" << endl;
    }

    return 0;
}
