#include <iostream>
using namespace std;

#define QUEUE_SIZE 100

class Queue {
public:
    int data[QUEUE_SIZE];
    int head;
    int tail;
    int length;

    Queue(int len) {
        head = 1;
        tail = 1;
        length = len;
    }

    void Enqueue(int x) {
        data[tail] = x;
        if (tail == length) {
            tail = 1;
        } else {
            tail++;
        }
    }

    int Dequeue() {
        int x = data[head];
        if (head == length) {
            head = 1;
        } else {
            head++;
        }
        return x;
    }
};

int main() {
    Queue Q(QUEUE_SIZE);

    Q.Enqueue(10);
    Q.Enqueue(20);
    Q.Enqueue(30);

    cout << "Dequeued element: " << Q.Dequeue() << endl;
    cout << "Dequeued element: " << Q.Dequeue() << endl;
    cout << "Dequeued element: " << Q.Dequeue() << endl; 

    return 0;
}

/*
Output:

Dequeued element: 10
Dequeued element: 20
Dequeued element: 30

*/
