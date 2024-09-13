#include <iostream>

using namespace std;

void merge(int arr[], int temp[], int start, int mid, int end) {
    int i = start;   
    int j = mid;     
    int k = start; 

    while (i < mid && j < end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[k++] = arr[i++];
    }

    while (j < end) {
        temp[k++] = arr[j++];
    }

    for (i = start; i < end; i++) {
        arr[i] = temp[i];
    }
}


void mergeSort(int arr[], int n) {
    int temp[n];

    for (int subArraySize = 1; subArraySize < n; subArraySize *= 2) {
        for (int start = 0; start < n; start += 2 * subArraySize) {
            int mid = std::min(start + subArraySize, n);
            int end = std::min(start + 2 * subArraySize, n);
            merge(arr, temp, start, mid, end);
        }
    }
}


int main() {
    int arr[] = {5,2,4,7,1,3,2,6};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, n);

    for(int i=0; i<n; i++) {
        cout<< arr[i] << " ";
    }

    return 0;
}

// Output: 1 2 2 3 4 5 6 7