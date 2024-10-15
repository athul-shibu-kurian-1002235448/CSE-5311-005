#include <iostream>
using namespace std;

#define STACK_SIZE 100

class Stack {
public:
    int data[STACK_SIZE];
    int top;

    Stack() {
        top = 0;
    }

    bool Stack_Empty() {
        return top == 0;
    }

    void Push(int x) {
        if (top < STACK_SIZE) {
            top++;
            data[top] = x;
        } else {
            cout << "Error: Stack overflow" << endl;
        }
    }

    int Pop() {
        if (Stack_Empty()) {
            cout << "Error: Stack underflow" << endl;
            return -1;
        } else {
            top--;
            return data[top + 1];
        }
    }
};

int main() {
    Stack S;

    S.Push(10);
    S.Push(20);
    S.Push(30);

    cout << "Popped element: " << S.Pop() << endl;
    cout << "Popped element: " << S.Pop() << endl;
    cout << "Popped element: " << S.Pop() << endl;
    cout << "Popped element: " << S.Pop() << endl;

    return 0;
}


/*

Output:

Popped element: 30
Popped element: 20
Popped element: 10
Popped element: Error: Stack underflow
-1

*/