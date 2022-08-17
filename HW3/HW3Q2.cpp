#include <iostream>
#include <random>
#include <math.h>
using namespace std;

const int M1 = 97;      // m1 size
const int M2 = 98;      // m2 size
const int M3 = 100;     // m3 size
const int M4 = 101;     // m4 size
const int NUM = 1000;   // number of rarrayndom integers
const int MAX = 122804; // max integer
const int MIN = -1;     // min integer
const int NULLK = 0;    // NULL key

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
        // cout << "array[" << lower << ":" << upper << "] already sorted" << endl;
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

/**
 * @brief hash function
 * @param key    key in the hash table
 * @param m    size of hash table
 */
int hash1(int key, int m)
{
    int result = key % m;
    return result;
}

/**
 * @brief insert integer to hash table
 * @param M    hash table
 * @param key  key in the hash table
 * @param m    size of hash table
 */
int insert(int M[], int key, int m)
{
    // hash
    int j = hash1(key, m);
    // collision times +1 in position j
    M[j]++;
    return j;
}

/**
 * @brief find minimum number in the table
 * @param M     hash table
 * @param m     size of hash table
 */
int min(int M[], int m)
{
    mergeSort(M, 0, m);
    return M[0];
}

/**
 * @brief find maximum number in the table
 * @param M     hash table
 * @param m     size of hash table
 */
int max(int M[], int m)
{
    mergeSort(M, 0, m);
    return M[m];
}

/**
 * @brief find average in the table
 * @param M     hash table
 * @param m     size of hash table
 */
double avg(int M[], int m)
{
    double sum = 0.0;
    // sum
    for (int i = 0; i < m; i++)
    {
        sum += double(M[i]);
    }
    // avg
    return double(sum / m);
}

/**
 * @brief find variance in the table
 * @param M     hash table
 * @param m     size of hash table
 * @param avg   average of the table
 */
double var(int M[], int m, double avg)
{
    double sum = 0.0;
    // sum
    for (int i = 0; i < m; i++)
    {
        sum += pow(double(M[i]) - avg, 2);
    }
    // variance
    return sqrt(sum);
}

int main()
{
    int *array = new int[NUM]; // random array
    int *m1 = new int[M1];     // hash table 1
    int *m2 = new int[M2];     // hash table 2
    int *m3 = new int[M3];     // hash table 3
    int *m4 = new int[M4];     // hash table 4
    random_device rd;
    mt19937 gen1(rd()); // generator for year
    uniform_int_distribution<> distribY(0, 4);
    mt19937 gen2(rd()); // generator for month
    uniform_int_distribution<> distribM(1, 12);
    mt19937 gen3(rd()); // generator for day
    uniform_int_distribution<> distribD(1, 28);

    // generate the random array
    for (int i = 0; i < NUM; i++)
    {
        int year = distribY(gen1);
        int month = distribM(gen2);
        int day = distribD(gen3);
        // put together to get birthday
        array[i] = month * 10000 + day * 100 + year;
        cout << array[i] << " ";
    }
    cout << endl;

    cout << "For hash table with size m1:" << endl;
    // hash tabel 1 initialize
    for (int i = 0; i < M1; i++)
    {
        m1[i] = NULLK;
    }
    // hash
    for (int i = 0; i < NUM; i++)
    {
        insert(m1, array[i], M1);
    }
    // except the first hash value
    for (int i = 0; i < M1; i++)
    {
        if (m1[i] > 0)
            m1[i]--;
        // output collision
        // cout << m1[i] << " ";
    }
    // result for hash table 1
    cout << "min: " << min(m1, M1) << endl;
    cout << "max: " << max(m1, M1) << endl;
    cout << "average: " << avg(m1, M1) << endl;
    cout << "variance: " << var(m1, M1, avg(m1, M1)) << endl;
    cout << endl;

    cout << "For hash table with size m2:" << endl;
    // hash table 2 initialize
    for (int i = 0; i < M2; i++)
    {
        m2[i] = NULLK;
    }
    // hash
    for (int i = 0; i < NUM; i++)
    {
        insert(m2, array[i], M2);
    }
    // except the first hash value
    for (int i = 0; i < M2; i++)
    {
        if (m2[i] > 0)
            m2[i]--;
        // output collision
        // cout << m2[i] << " ";
    }
    // result for hash table 2
    cout << "min: " << min(m2, M2) << endl;
    cout << "max: " << max(m2, M2) << endl;
    cout << "average: " << avg(m2, M2) << endl;
    cout << "variance: " << var(m2, M2, avg(m2, M2)) << endl;
    cout << endl;

    cout << "For hash table with size m3:" << endl;
    // hash table 3 initialize
    for (int i = 0; i < M3; i++)
    {
        m3[i] = NULLK;
    }
    // hash
    for (int i = 0; i < NUM; i++)
    {
        insert(m3, array[i], M3);
    }
    // except the first hash value
    for (int i = 0; i < M3; i++)
    {
        if (m3[i] > 0)
            m3[i]--;
        // output collision
        // cout << m3[i] << " ";
    }
    // result for hash table 3
    cout << "min: " << min(m3, M3) << endl;
    cout << "max: " << max(m3, M3) << endl;
    cout << "average: " << avg(m3, M3) << endl;
    cout << "variance: " << var(m3, M3, avg(m3, M3)) << endl;
    cout << endl;

    cout << "For hash table with size m4:" << endl;
    // hash table 4 initialize
    for (int i = 0; i < M4; i++)
    {
        m4[i] = NULLK;
    }
    // hash
    for (int i = 0; i < NUM; i++)
    {
        insert(m4, array[i], M4);
    }
    // except the first hash value
    for (int i = 0; i < M4; i++)
    {
        if (m4[i] > 0)
            m4[i]--;
        // output collision
        // cout << m4[i] << " ";
    }
    // result for hash table 4
    cout << "min: " << min(m4, M4) << endl;
    cout << "max: " << max(m4, M4) << endl;
    cout << "average: " << avg(m4, M4) << endl;
    cout << "variance: " << var(m4, M4, avg(m4, M4)) << endl;
    cout << endl;
    return 0;
}