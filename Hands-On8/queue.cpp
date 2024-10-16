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

    bool Queue_Empty() {
        return head == tail;
    }

    bool Queue_Full() {
        return (tail + 1 == head) || (tail == length && head == 1);
    }

    void Enqueue(int x) {
        if (Queue_Full()) {
            cout << "Error: Queue overflow" << endl;
            return;
        }
        data[tail] = x;
        if (tail == length) {
            tail = 1;
        } else {
            tail++;
        }
    }

    int Dequeue() {
        if (Queue_Empty()) {
            cout << "Error: Queue underflow" << endl;
            return -1;
        }
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

    cout << "Dequeued element: " << Q.Dequeue() << endl;

    for (int i = 1; i < QUEUE_SIZE; i++) {
        Q.Enqueue(i);
    }

    Q.Enqueue(101);

    return 0;
}
