/**
 *   @file     16ex01.c
 *   @date     2020-01-23
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    determine system's byte ordering
 */

#include <iostream>
using namespace std;

int main() {
    int n = 1;
    if (*(char*)&n == 1) {
        cout << "little-endian" << endl;
    } else {
        cout << "end-endian" << endl;
    }

    return 0;
}
