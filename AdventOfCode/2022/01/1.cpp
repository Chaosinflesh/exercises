// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    int current = 0;
    for (std::string line; std::getline(input, line);) {
        if (line.empty()) {
            max3 = current > max3 ? current : max3;
            if (max3 > max2) {
                std::swap(max3, max2);
            }
            if (max2 > max1) {
                std::swap(max2, max1);
            }
            current = 0;
        } else {
            current += std::stod(line);
        }
    }
    std::cout << "A: " << max1 << "\tB: " << (max1 + max2 + max3) << std::endl;
    
    return 0;
}
