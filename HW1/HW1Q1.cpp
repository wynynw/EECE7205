#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

/**
 * @brief swap x and y uxing pass-by-pointer
 * @param x    pointer for x
 * @param y    pointer for y
 */
void SwapP(int *x, int *y)
{

    int temp = *x; //middle params for swap
    *x = *y;
    *y = temp;
}

/**
 * @brief swap x and y uxing pass-by-reference
 * @param x    reference for x
 * @param y    reference for y
 */
void SwapR(int &x, int &y)
{
    int temp = x; //middle params for swap
    x = y;
    y = temp;
}

//test
int main()
{
    int x = 7;   //test x
    int y = 205; //test y
    cout << "Before Swap, x=" << x << ", y=" << y << endl;
    SwapP(&x, &y); //swap by pointer
    cout << "After SwapP, x=" << x << ", y=" << y << endl;
    SwapR(x, y); //swap by reference
    cout << "After SwapR, x=" << x << ", y=" << y << endl;
}