#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomized_partition(vector<int> &A, int start, int end) {
    srand(time(NULL));
    int rand_index = start + rand()%(end - start + 1);
    swap(A[rand_index], A[end]);
    int pivot = A[end], pivot_index = start;
    for(int j=start; j<=end-1; j++) {
        if(pivot >= A[j]) {
            swap(A[pivot_index], A[j]); //a[i] < pivot, so swap it with an element that's > pivot
            pivot_index++; //keeps track of the final position of the pivot element by counting the number of elements less than it
        }
    }
    swap(A[pivot_index], A[end]); //put pivot(A[end]) in the correct position (pivot_index)
    return pivot_index;
}

//selects and displays the i-th smallest number, also called the i-th order statistic
int randomized_quick_select(vector<int>& A, int start, int end, int i) {
    if(start<end) {
        int q = randomized_partition(A, start, end);
        int k = q - start + 1;
        if(i == k) {
            return A[q];
        } else if(i < k) {
            return randomized_quick_select(A, start, q-1, i);
        } else {
            return randomized_quick_select(A, q+1, end, i-k);
        }
    } else {
        return A[start];
    }
}

int main() {
    
    vector<int> A = {2, 8, 7, 1, 3, 5, 6, 4};

    int n = A.size();
    
    cout<<"The 5th order statistic of the array A is: "<<randomized_quick_select(A, 0, n-1, 5);

    return 0;
}


//Outout: The 5th order statistic of the array A is: 5