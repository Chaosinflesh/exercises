// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <iostream>

int main(int argc, char** argv) {
    long sum = 0L;
    for (int i = 0, j = 0; i < 1000; i +=3) {
        sum += i;
        if (j < i) {
            sum += j;
        }
        if (j <= i) {
            j += 5;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
