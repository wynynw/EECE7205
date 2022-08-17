#include <iostream>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

int F1(int n)
{
    if (n == 0)
        return 1;
    return F1(n - 1) + F1(n - 1);
}
int F2(int n)
{
    if (n == 0)
        return 1;
    if (n % 2 == 0)
    {
        int result = F2(n / 2);
        return result * result;
    }
    else
        return 2 * F2(n - 1);
}

int main()
{
    // initialize
    clock_t startF1, endF1;
    clock_t startF2, endF2;

    // test two functions
    for (int i = 0; i < 10; i++)
    {
        cout << "F1: " << F1(i) << ", F2: " << F2(i) << endl;
    }

    // get the speed of F1 when n=30
    cout << "When n=30: " << endl;
    startF1 = clock();
    F1(30);
    endF1 = clock();
    cout << "F1 time = " << double(endF1 - startF1) / CLOCKS_PER_SEC << "s" << endl;
    // get the speed of F2 when n=30
    startF2 = clock();
    F2(30);
    endF2 = clock();
    cout << "F2 time = " << double(endF2 - startF2) / CLOCKS_PER_SEC << "s" << endl;
}
