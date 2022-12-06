// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");
    std::regex reg("(\\d+)-(\\d+),(\\d+)-(\\d+)");
    std::smatch sm;

    int count = 0;
    int overlap = 0;
    int arr[4];
    for (std::string line; std::getline(input, line);) {

        std::regex_match(line, sm, reg, std::regex_constants::match_default);
        for (auto i = 1; i < sm.size(); i++) {
            arr[i - 1] = std::stod(sm[i]);
        }
        if (arr[0] <= arr[2] && arr[1] >= arr[3] || arr[2] <= arr[0] && arr[3] >= arr[1]) {
            count++;
        }
        if (arr[2] <= arr[1] && arr[3] >= arr[0] || arr[0] <= arr[3] && arr[1] >= arr[2]) {
            overlap++;
        }
    }
    std::cout << count << " " << overlap << std::endl;
    
    return 0;
}
