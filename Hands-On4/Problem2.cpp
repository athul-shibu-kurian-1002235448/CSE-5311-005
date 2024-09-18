#include <iostream>

using namespace std;

int main()
{
    
    //Enter input array here
    int array1[] = {1, 2, 3, 3, 3, 3, 4, 5, 5};

    int N1 = sizeof(array1) / sizeof(array1[0]);

    if (N1 > 1)
    {
        int j = 0;
        for (int i = 1; i < N1; i++)
        {
            if (array1[j] != array1[i])
            {
                j++;
                array1[j] = array1[i];
            }
        }
        N1 = j + 1;
    }

    for (int i = 0; i < N1; i++)
    {
        cout << array1[i];
        if (i < N1 - 1) std::cout << ", ";
    }

    return 0;
}


/*

Time complexity proof:

The time complexity of the algorithm is O(N), where N is the size of the input array. 
This is because the algorithm uses a single loop that iterates through the array exactly once.
In each iteration, it performs constant-time operations: comparing elements and, when necessary, updating the position of unique elements. 
Since there are no nested loops or recursive calls, the total time taken scales linearly with the number of elements.

Ways to improve:

Applying a divide and conquer approach can enhance performance, especially for large arrays. 
By splitting the array into smaller subarrays, processing each independently to remove duplicates,
and then merging the results while ensuring no duplicates across subarrays, the efficiency can be improved.

*/