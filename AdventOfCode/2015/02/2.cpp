// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>

using std::string;

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");
    std::regex reg("(\\d+)x(\\d+)x(\\d+)");
    std::smatch sm;

    int total = 0;
    int ribbons = 0;
    for (string line; std::getline(input, line);) {
        std::regex_match(line, sm, reg, std::regex_constants::match_default);
        int l = std::stoi(sm[1]);
        int w = std::stoi(sm[2]);
        int h = std::stoi(sm[3]);
        int max = l > w ? l : w;
        max = max > h ? max : h;
        total += 2 * (l * w + l * h + w * h) + (l * w * h) / max;
        ribbons += 2 * (l + w + h - max) + l * w * h;
        
    }
    std::cout << "A: " << total << "\tB: " << ribbons << std::endl;

    return 0;
}
