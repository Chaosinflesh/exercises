// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>

using std::string;

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    int floor = 0;
    int basement = 0;
    string line;
    std::getline(input, line);
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(') {
            floor++;
        } else {
            floor--;
        }
        if (basement == 0 && floor == -1) {
            basement = i + 1;
        }
    }

    std::cout << "A: " << floor << "\tB: " << basement << std::endl;

    return 0;
}
