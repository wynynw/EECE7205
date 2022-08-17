#include <iostream>
#include <time.h>

using namespace std;
int *A; // Fibonacci array

/**
 * @brief      dynamic programming
 * @param n    nth number in fibonacci array
 */
int FibonacciD(int n)
{
    if (A[n] < 0)
    {
        if (n <= 1)
            return n;                                 // n=0 and n=1
        A[n] = FibonacciD(n - 1) + FibonacciD(n - 2); // sort the value
    }
    return A[n];
}

/**
 * @brief      recursive
 * @param n    nth number in fibonacci array
 */
int FibonacciR(int n)
{
    if (n <= 1)
        return n;                                 // n=0 and n=1
    return FibonacciR(n - 1) + FibonacciR(n - 2); // recursive
}

int main()
{
    clock_t start, end;
    int n; // The user inputs this number to calculate its Fibonacci sequence
    cout << "n = ";
    cin >> n;
    A = new int[n];
    // initialize all elements in array A to an invalid Fibonacci value
    for (int i = 0; i <= n; i++)
        A[i] = -1;
    cout.setf(ios::fixed, ios::floatfield); // set output without scientific notation
    start = clock();
    // Find Fibonacci sequence n using the Dynamic programming function
    cout << " FibonacciD(n) = " << FibonacciD(n);
    end = clock();
    cout << "\nRunning time of fD with n=" << n << " is: "
         << end - start // count time
         << "(" << (double)(end - start) / CLOCKS_PER_SEC << "s)"// output seconds
         << endl; 

    start = clock();
    // Find Fibonacci sequence n using the recursive only function
    cout << "\n FibonacciR(n) = " << FibonacciR(n);
    end = clock();
    cout << "\n Running time of fR with n=" << n << " is: "
         << end - start // count time
         << "(" << (double)(end - start) / CLOCKS_PER_SEC << "s)"// output seconds
         << endl; 
    return 0;
}