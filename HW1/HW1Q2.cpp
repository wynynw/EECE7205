#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

/**
 * @brief mirror the array
 * @param v      input array
 * @param len length of the array
 * */
void mirror(int v[], int len)
{
    //the center of the array(end of the swap)
    int flag = len / 2;
    for (int i = 0; i < flag; i++)
    {
        //The goal position of v[i]
        //minus 1 because positions start from 0
        int j = len - i - 1;
        //swap v[i] with goal position
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

//test
int main()
{
    // Declare array
    int v[] = {5, 6, 7, 8, 2, 1};
    // mirror it
    mirror(v, 6);
    // Print array
    for (int i = 0; i < 6; i++)
        cout << v[i] << '\n';
    return 0;
}
