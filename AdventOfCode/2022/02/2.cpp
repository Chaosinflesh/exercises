// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>

int get_scoreA(int a, int b) {
    std::cout << a << "," << b << std::endl;
    int t = 10 * a + b;
    switch (t) {
        // Draws
        case 0:
        case 11:
        case 22:
            return b + 4;
        // They win
        case 10:
        case 21:
        case 2:
            return b + 1;
        // Scissors wins
        default:
            return b + 7;
    }
}

int get_scoreB(int a, int b) {
    std::cout << a << "," << b << std::endl;
    int t = 10 * a + b;
    switch (t) {
        // Draws
        case 1:
        case 11:
        case 21:
            return a + 4;
        // They win
        case 0:
        case 10:
        case 20:
            return (a + 2) % 3 + 1;
        // I win:
        default:
            return (a + 1) % 3 + 7;
    }
}

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    int a = 0, b = 0;
    for (std::string line; std::getline(input, line);) {
        a += get_scoreA(line[0] - 'A', line[2] - 'X');
        b += get_scoreB(line[0] - 'A', line[2] - 'X');
    }
    std::cout << "A: " << a << "\tB: " << b << std::endl;
    
    return 0;
}
