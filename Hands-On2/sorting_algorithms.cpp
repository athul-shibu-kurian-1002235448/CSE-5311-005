#include <iostream>

using namespace std;

// 1. INSERTION SORT
void insertion_sort(int a[], int n) {
    int i, key;
    for(int j=1; j<=n-1; j++) {
        key = a[j];
        i = j-1;
        while(i>=0 && a[i]>key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}



// 2. SELECTION SORT
void selection_sort(int a[], int n) {
    int min;
    for(int i=0; i<=n-2; i++) {
        min = i;
        for(int j=i+1; j<=n-1; j++) {
            if(a[j]<a[min]) {
                min=j;
            }
        }
        swap(a[min],a[i]);
    }
}



// 3. BUBBLE SORT
void bubble_sort(int a[], int n) {
    bool swapped;
    for(int i=0; i<=n-2; i++) {
        swapped = false;
        for(int j=n-1; j>=i+1; j--) {
            if(a[j] < a[j-1]) {
                swap(a[j], a[j-1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
}



