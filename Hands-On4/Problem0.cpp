#include <iostream>

using namespace std;

int fib(int n) {

    static int call_stack[100];
    static int depth = 0;

    call_stack[depth] = n;
    depth++;

    for (int i = 0; i < depth; ++i) {
        cout<<"fib("<<call_stack[i]<<")";
        if (i != depth - 1) {
            cout<<" -> ";
        }
    }
    
    cout<<"\n";

    if (n == 0) {
        depth--;
        return 0;
    } else if (n == 1) {
        depth--;
        return 1; 
    } else {
        int result = fib(n - 1) + fib(n - 2);
        depth--;
        return result; //This would give the exact same result as doing "return fib(n-1) + fib(n-2)"
    }
}

int main() {
    int result = fib(5);
    cout<<"fib(5) = "<<result<<"\n";
    return 0;
}

/*

fib(5)
fib(5) -> fib(4)
fib(5) -> fib(4) -> fib(3)
fib(5) -> fib(4) -> fib(3) -> fib(2)
fib(5) -> fib(4) -> fib(3) -> fib(2) -> fib(1)
fib(5) -> fib(4) -> fib(3) -> fib(2) -> fib(0)
fib(5) -> fib(4) -> fib(3) -> fib(1)
fib(5) -> fib(4) -> fib(2)
fib(5) -> fib(4) -> fib(2) -> fib(1)
fib(5) -> fib(4) -> fib(2) -> fib(0)
fib(5) -> fib(3)
fib(5) -> fib(3) -> fib(2)
fib(5) -> fib(3) -> fib(2) -> fib(1)
fib(5) -> fib(3) -> fib(2) -> fib(0)
fib(5) -> fib(3) -> fib(1)
fib(5) = 5

*/