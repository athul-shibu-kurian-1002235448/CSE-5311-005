#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>    

using namespace std;

int Partition(vector<int>& A, int p, int r) {
    int x = A[r]; 
    int i = p - 1;
    for (int j = p; j <= r - 1; ++j) {
        if (A[j] <= x) {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int Randomized_Partition(vector<int>& A, int p, int r) {
    int i = p + rand() % (r - p + 1); 
    swap(A[r], A[i]);
    return Partition(A, p, r);
}

void Randomized_Quicksort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = Randomized_Partition(A, p, r);
        Randomized_Quicksort(A, p, q - 1);
        Randomized_Quicksort(A, q + 1, r);
    }
}

int main() {
    srand(time(0));

    vector<int> A = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};

    int n = A.size();

    Randomized_Quicksort(A, 0, n-1);

    for (int i = 0; i < n; ++i) {
        cout << A[i] << " ";
    }

    cout << endl;

    return 0;
}
