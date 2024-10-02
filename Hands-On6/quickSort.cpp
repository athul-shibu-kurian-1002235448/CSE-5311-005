//Requires C++11 or above

#include <iostream>
#include <vector>

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

void Quicksort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        Quicksort(A, p, q - 1);
        Quicksort(A, q + 1, r);
    }
}

int main() {
    
    vector<int> A = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};

    int n = A.size();

    Quicksort(A, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}
