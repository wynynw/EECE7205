#include <iostream>
#include <string.h>
#include <fstream>
#include <stdexcept>
using namespace std;

int moves; // global variable moves
int comps; // global variable comps

/******************************SORT ALGORITHMS******************************/
/**
 * @brief swap x and y
 * @param x    reference for x
 * @param y    reference for y
 */
void swap(int &x, int &y)
{
    int temp = x; // middle params for swap
    x = y;
    y = temp;
    moves += 3;
}

/**
 * @brief insertionSort
 * @param arr  Array to be sorted
 * @param n    Array length
 */
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            comps += 1; // compare
            arr[j + 1] = arr[j];
            moves += 1; // move
            j = j - 1;
        }
        comps += 1; // the last comparasion
        if (i != j + 1)
        {
            arr[j + 1] = key;
            moves += 1; // move
        }
    }
}

/**
 * @brief heapify
 * @param arr  Array to be sorted
 * @param n    Array length
 * @param i    parents nodes
 */
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // If left child is larger than root
    comps += 1;
    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
    }

    // If right child largest
    comps += 1;
    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }

    // If root is nor largest
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        // Recursively heapifying the sub-tree
        heapify(arr, n, largest);
    }
}

/**
 * @brief heapSort
 * @param arr  Array to be sorted
 * @param n    Array length
 */
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // Moving current root to end
        swap(arr[0], arr[i]);
        // Calling max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

/**
 * @brief partition
 * takes last element as pivot, places the pivot element at its correct
 * position in sorted array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right of pivot
 * @param arr  Array to be sorted
 * @param p    Starting index
 * @param r    Ending index
 */
int partition(int arr[], int p, int r)
{
    int pivot = arr[r]; // pivot
    // Index of smaller element
    // and indicates the right position of pivot found so far
    int i = (p - 1);

    for (int j = p; j < r; j++)
    {
        // If current element is smaller than the pivot
        comps += 1;
        if (arr[j] <= pivot)
        {
            i++;        // increment index of smaller element
            if (i != j) // avoid unnecessary increment
            {
                swap(arr[i], arr[j]);
            }
        }
    }
    if (r != i + 1) // avoid unnecessary increment
    {
        swap(arr[i + 1], arr[r]);
    }
    return (i + 1);
}

/**
 * @brief QuickSort
 * @param arr    Array to be sorted
 * @param p    Starting index
 * @param r    Ending index
 */
void quickSort(int arr[], int p, int r)
{
    if (p < r)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int q = partition(arr, p, r);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
}
/***************************************************************************/

/******************************TEST FUNCTIONS*******************************/
/**
 * @brief copy arrays
 * @param copy   Copied to
 * @param arr    Copied from
 * @param len    Array length
 */
void copyArray(int copy[], int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        copy[i] = arr[i];
    }
}

/**
 * @brief generate arrays
 * @param BST   best case array(sorted in ascending)
 * @param AVG   average case array(random)
 * @param WST   worst case array(sorted in descending)
 * @param len   Array length
 */
void genArrays(int BST[], int AVG[], int WST[], int len)
{
    // call this only once at the beginning to
    // allow rand() to generate a different
    // succession of random values.
    srand(time(NULL));
    // Generate BST
    for (int i = 0; i < len; i++)
    {
        BST[i] = i * 10;
    }
    // Generate AVG
    for (int i = 0; i < len; i++)
    {
        AVG[i] = rand() % 100000;
    }
    // Generage WST
    for (int i = 0; i < len; i++)
    {
        WST[i] = 10000 - i * 10;
    }
}

/**
 * @brief test if the array is sorted
 * @param arr   test array
 * @param len   Array length
 */
bool testArray(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        // if not sorted
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

/***************************************************************************/
int main()
{
    int len = 1000; // length of the array
    int BST[len];   // best case array(sorted in ascending)
    int tBST[len];  // test best case
    int AVG[len];   // average case array(random)
    int tAVG[len];  // test average case
    int WST[len];   // worst case array(sorted in descending)
    int tWST[len];  // test worst case
    ofstream outf;  // output file stream
    // open file
    outf.open("sort.txt");
    if (outf.fail())
    {
        cerr << "Error: Could not open output file\n";
        exit(1);
    }

    // generate arrays
    genArrays(BST, AVG, WST, len);

    /***********test with the copy of best case array***********/
    outf << "Best" << endl;

    // copy the array to test insertion sort
    // e.g. copy BST to tBST
    copyArray(tBST, BST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    insertionSort(tBST, len);
    // test the result array
    cout << boolalpha
         << "BST-INSERTIONSORT " << testArray(tBST, len) << endl;
    // save the results to file
    outf << "INSERTIONSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test heap sort
    copyArray(tBST, BST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    heapSort(tBST, len);
    // test the result array
    cout << boolalpha
         << "BST-HEAPSORT " << testArray(tBST, len) << endl;
    // save the results to file
    outf << "HEAPSORT \t\t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test quick sort
    copyArray(tBST, BST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    quickSort(tBST, 0, len - 1);
    // test the result array
    cout << boolalpha
         << "BST-QUICKSORT " << testArray(tBST, len) << endl;
    // save the results to file
    outf << "QUICKSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    outf << endl;

    /***********test with the copy of average case array***********/
    outf << "Average" << endl;

    // copy the array to test insertion sort
    // e.g. copy BST to tBST
    copyArray(tAVG, AVG, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    insertionSort(tAVG, len);
    // test the result array
    cout << boolalpha
         << "AVG-INSERTIONSORT " << testArray(tAVG, len) << endl;
    // save the results to file
    outf << "INSERTIONSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test heap sort
    copyArray(tAVG, AVG, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    heapSort(tAVG, len);
    // test the result array
    cout << boolalpha
         << "AVG-HEAPSORT " << testArray(tAVG, len) << endl;
    // save the results to file
    outf << "HEAPSORT \t\t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test quick sort
    copyArray(tAVG, AVG, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    quickSort(tAVG, 0, len - 1);
    // test the result array
    cout << boolalpha
         << "AVG-QUICKSORT " << testArray(tAVG, len) << endl;
    // save the results to file
    outf << "QUICKSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    outf << endl;

    /***********test with the copy of worst case array***********/
    outf << "Worst" << endl;

    // copy the array to test insertion sort
    // e.g. copy BST to tBST
    copyArray(tWST, WST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    insertionSort(tWST, len);
    // test the result array
    cout << boolalpha
         << "WST-INSERTIONSORT " << testArray(tWST, len) << endl;
    // save the results to file
    outf << "INSERTIONSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test heap sort
    copyArray(tWST, WST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    heapSort(tWST, len);
    // test the result array
    cout << boolalpha
         << "WST-HEAPSORT " << testArray(tWST, len) << endl;
    // save the results to file
    outf << "HEAPSORT \t\t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    // copy the array to test quick sort
    copyArray(tWST, WST, len);
    // initialize moves and comps to zero
    moves = 0;
    comps = 0;
    // test algorithms
    quickSort(tWST, 0, len - 1);
    // test the result array
    cout << boolalpha
         << "WST-QUICKSORT " << testArray(tWST, len) << endl;
    // save the results to file
    outf << "QUICKSORT \t";
    outf << "moves: " << moves << "\t";
    outf << "comps: " << comps << endl;

    outf.close(); // Close the file
}
