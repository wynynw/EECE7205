#include <iostream>
#include <vector>
#include <string.h>
#include <random>

using namespace std;

/**
 * @brief MODIFIED MERGE function
 * Merge the two sorted sub-arrays, and skip the process if whole array is already sorted
 * @param array     array contains two sorted sub-arrays
 * @param lower     start position of the array
 * @param middle    middle position of the array
 * @param upper     end position of the array
 */
void merge(int array[], int lower, int middle, int upper)
{
    int i, j, k;
    int left[middle - lower + 1]; // the left portion of 'array[]'
    int right[upper - middle];    // the right portion of 'array[]'

    // if whole array is already sorted, skip
    if (array[middle] < array[middle + 1])
    {
        cout << "array[" << lower << ":" << upper << "] already sorted" << endl;
    }
    // whole array not already sorted, merge the sorted sub-arrays
    else
    {

        // copy appropriate elements from array[] to left[]
        for (i = 0; i < middle - lower + 1; i++)
            left[i] = array[lower + i];
        // copy appropriate elements from array[] to right[]
        for (j = 0; j < upper - middle; j++)
            right[j] = array[middle + 1 + j];
        i = 0;     // index of sub-array left[]
        j = 0;     // index of sub-array right[]
        k = lower; // index of merged array
        // ascending order
        for (k = lower; i < middle - lower + 1 && j < upper - middle; k++)
        {
            if (left[i] <= right[j])
                // storing value of left[i] in array[k] if the former is smaller
                array[k] = left[i++];
            else
                // storing value of right[j] in array[j] if the former is smaller
                array[k] = right[j++];
        }
        while (i < middle - lower + 1)
            // copy back the remaining elements of left[] to array[]
            array[k++] = left[i++];
        while (j < upper - middle)
            // copy back the remaining elements of right[] to array[]
            array[k++] = right[j++];
    }
}

/**
 * @brief merge sort
 * @param array unordered arrays
 * @param lower start position of the array
 * @param upper end position of the array
 */
void mergeSort(int array[], int lower, int upper)
{
    // array contains only one element
    if (lower >= upper)
        return;
    // sort the left portion of the array
    mergeSort(array, lower, (lower + upper) / 2);
    // sort the right portion of the array
    mergeSort(array, ((lower + upper) / 2) + 1, upper);
    // merge the two portions
    merge(array, lower, (lower + upper) / 2, upper);
}

int main()
{
    // initialize the generator
    default_random_engine e;
    uniform_int_distribution<int> generate(0, 100);
    int n;

    // get array size
    cout << "Input the value of n(1<n<=50)> ";
    cin >> n;
    // corner case handle
    if ((n < 1) || (n > 50))
    {
        cout << "n should in range (1,50]" << endl;
        return 0;
    }

    // generate ramdon array A
    int A[n];
    cout << "Before merge sort, the random array A is:  " << endl;
    for (int i = 0; i < n; i++)
    {
        // generate(e);
        A[i] = generate(e);
        cout << A[i] << " ";
    }
    cout << "\n";

    // sort
    mergeSort(A, 0, n - 1);

    // output sorted array
    cout << "After merge sort, the ordered array A is:  " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << "\n";

    // test modified merge function
    cout << "Before modified merge sort, the sorted array A is:  " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << "\n";

    // modified merge function
    // if array is already in order, return
    mergeSort(A, 0, n - 1);

    // output the results
    cout << "After modified merge sort, array A is:  " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << "\n";
}
