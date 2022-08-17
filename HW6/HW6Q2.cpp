#include <iostream>
#include <time.h>
#include <math.h>
#define INT_MIN -2147483648

using namespace std;

/**
 * @brief      dynamic programming storing function
 * @param price    price array
 * @param n        total length
 * @param r        result
 */
int cutRodDAux(int *price, int n, int *r)
{
    int val;
    if (r[n] >= 0)
    {
        return r[n]; // already calcualted
    }
    if (n == 0)
    {
        val = 0; // no length inputed
    }
    else
    {
        val = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            // storing
            val = max(val, price[i] + cutRodDAux(price, n - i, r));
        }
    }
    r[n] = val;
    return val;
}

/**
 * @brief      dynamic programming
 * @param price    price array
 * @param n        total length
 */
int cutRodD(int *price, int n)
{
    int *r = new int[n + 1];
    for (int i = 0; i <= n; i++)
    {
        r[i] = INT_MIN; // initialize to min
    }
    return cutRodDAux(price, n, r); // dp storing
}

/**
 * @brief      recursive
 * @param price    price array
 * @param n        total length
 */
int cutRodR(int *price, int n)
{
    if (n == 0)
        return 0;      // no length inputed
    int val = INT_MIN; // initialize to min
    for (int i = 1; i <= n; i++)
        val = max(val, price[i] + cutRodR(price, n - i)); // recursive
    return val;
}

int main()
{
    clock_t start, end; // count time
    int result;         // store result
    int n;              // The user inputs this number to calculate its Fibonacci sequence
    cout << "Input the length of the rod: ";
    cin >> n;
    int *price = new int[n + 1];
    price[0] = n;
    // initialize all elements in array price
    for (int i = 1; i <= n; i++)
    {
        // L=1
        if (i == 1)
            price[i] = 2;
        // L=rod size
        else if (i == n)
            price[i] = float(n * 2.5 - 1);
        // 1<L<rod size
        else
            price[i] = floor(i * 2.5);
    }

    cout.setf(ios::fixed, ios::floatfield); // set output without scientific notation

    start = clock();
    // Find max price of length n using the Dynamic programming function
    result = cutRodD(price, n);
    end = clock();
    // if running time is less than 2 mins
    if (((double)(end - start) / CLOCKS_PER_SEC) <= 120)
    {
        cout << " CutRodD with n = " << n << " is " << result;
        cout << "\n Running time is " << end - start << endl; // output seconds
    }
    // if running time is more than 2 mins
    else
    {
        cout << "\n cutRodR with n = " << n
             << "\n No result in 2 mins\n";
    }

    start = clock();
    // Find ax price of length n using the Dynamic programming function
    result = cutRodR(price, n);
    end = clock();
    // if running time is less than 2 mins
    if (((double)(end - start) / CLOCKS_PER_SEC) <= 120)
    {
        cout << " CutRodR with n = " << n << " is " << result;
        cout << "\n Running time is " << end - start << endl; // output seconds
    }
    // if running time is more than 2 mins
    else
    {
        cout << "\n cutRodR with n = " << n
             << "\n No result in 2 mins\n";
    }
    return 0;
}