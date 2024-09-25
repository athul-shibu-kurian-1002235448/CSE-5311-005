#include <iostream>
#include <vector>

using namespace std;

// The user may use any struct as long as it has the member "key" of type int
struct Node {
    int key;
    int value;

    Node(int k = 0, int val = 0) : key(k), value(val) {}
};

class MinHeap {
public:
    vector<Node> heap;

    int parent(int i) {
        return (i - 1) >> 1;
    }

    int left(int i) {
        return (i << 1) + 1;
    }

    int right(int i) {
        return (i << 1) + 2;
    }

    MinHeap() {}

    void minHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap.size() && heap[l].key < heap[i].key)
            smallest = l;
        if (r < heap.size() && heap[r].key < heap[smallest].key)
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }

    void buildMinHeap(vector<Node>& data) {
        heap = data;
        for (int i = (heap.size() >> 1) - 1; i >= 0; i--) {
            minHeapify(i);
        }
    }

    void insert(Node& element) {
        heap.push_back(element);
        int i = heap.size() - 1;
        while (i != 0 && heap[parent(i)].key > heap[i].key) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    Node pop() {
        if (heap.empty()) {
            cout << "Heap is empty. Cannot pop.\n";
            return Node(); // Return a default Node
        }
        Node poppedNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            minHeapify(0);
        return poppedNode;
    }

    bool isEmpty() {
        return heap.empty();
    }

    void printHeap() {
        for (size_t i = 0; i < heap.size(); ++i) {
            cout << "(key: " << heap[i].key << ", data: " << heap[i].value << ") ";
        }
        cout << endl;
    }
};

int main() {

    vector<Node> data;

    data.push_back(Node(5, 50));
    data.push_back(Node(3, 30));
    data.push_back(Node(17, 170));
    data.push_back(Node(10, 100));
    data.push_back(Node(84, 840));
    data.push_back(Node(19, 190));
    data.push_back(Node(6, 60));
    data.push_back(Node(22, 220));
    data.push_back(Node(9, 90));

    // ability to initially build the heap:
    MinHeap minHeap;
    minHeap.buildMinHeap(data);

    cout << "Min Heap after buildMinHeap:\n";
    minHeap.printHeap();

    /*
        //output:

        Min Heap after buildMinHeap:
        (key: 3, data: 30) (key: 5, data: 50) (key: 6, data: 60) (key: 9, data: 90) (key: 84, data: 840) (key: 19, data: 190) (key: 17, data: 170) (key: 22, data: 220) (key: 10, data: 100)
    */


    //ability to min heapify:
    minHeap.heap[0].key = 100;  //violating min heap property

    minHeap.minHeapify(0); //heapifying
    
    cout << "\nAfter changing root node to 100 and Heapifying:\n";
    minHeap.printHeap();

     /*
        //output:

        After changing root node to 100 and Heapifying:
        (key: 5, data: 50) (key: 9, data: 90) (key: 6, data: 60) (key: 10, data: 100) (key: 84, data: 840) (key: 19, data: 190) (key: 17, data: 170) (key: 22, data: 220) (key: 100, data: 30)
    */


    //ability to pop root node and re-heapify:
    Node poppedRootNode = minHeap.pop();

    cout<<"Popped Node:\n";
    cout << "(key: " << poppedRootNode.key << ", data: " << poppedRootNode.value << ") ";

    cout<<"\nHeap after popping Root node:\n";
    minHeap.printHeap();

    /*
        //output:

        Popped Node:
        (key: 5, data: 50)
        Heap after popping Root node:
        (key: 6, data: 60) (key: 9, data: 90) (key: 17, data: 170) (key: 10, data: 100) (key: 84, data: 840) (key: 19, data: 190) (key: 100, data: 30) (key: 22, data: 220)
    */

    return 0;
}
