#include <iostream>

using namespace std;

int MAX_K = 100;
int MAX_N = 1000;
int MAX_TOTAL = MAX_K * MAX_N;

int main() {
    int K, N;
    cin >> K >> N;

    if (K > MAX_K || N > MAX_N) {
        return 1;
    }

    int arrays[MAX_K][MAX_N];
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < N; j++) {
            cin >> arrays[i][j];
        }
    }

    int total = K * N;
    int result[MAX_TOTAL];
    int indices_arr[MAX_K];
    for(int i = 0; i < K; i++) {
        indices_arr[i] = 0;
    }

    for(int i = 0; i < total; i++) {
        int min_val;
        int min_array = -1;
        for(int j = 0; j < K; j++) {
            if(indices_arr[j] < N) {
                if(min_array == -1 || arrays[j][indices_arr[j]] < min_val) {
                    min_val = arrays[j][indices_arr[j]];
                    min_array = j;
                }
            }
        }
        if(min_array != -1) {
            result[i] = min_val;
            indices_arr[min_array]++;
        }
    }

    for(int i = 0; i < total; i++) {
        cout << result[i];
        if(i != total - 1) {
            cout << " ";
        }
    }
    cout<<"\n";

    return 0;
}


/*

2. Time Complexity proof:

This algorithm repeatedly selects the smallest current element from the heads of the K arrays and appends it to the result array. 
Since there are a total of T = K * N elements to merge, this selection process is performed T times.
At each step, finding the smallest element among the K current elements requires O(K) time,
because it involves comparing each of the K elements. 
Therefore, the time taken per element is O(K), leading to an overall time complexity of O(T * K) = O(K * N * K) = O(K^2 * N). 

3. Ways to improve:

This can be improved by adopting a divide and conquer approach that merges the arrays in pairs. 
By merging two arrays at a time, we reduce the number of arrays by half in each round, resulting in O(logK) rounds. 
This method lowers the overall time complexity to O(K*N*logK), making the algorithm much more efficient.
Performing this divide and conquer using loops instead of recursion would be more efficient.

*/