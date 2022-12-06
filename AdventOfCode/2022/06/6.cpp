// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

#define TOKEN_LENGTH 13

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");
    std::map<int, int> items;
    
    for (std::string line; std::getline(input, line);) {
        for (int pos = 0; pos < TOKEN_LENGTH; pos++) {
            items[line[pos]]++;
        }
        for (int pos = TOKEN_LENGTH; pos < line.length(); pos++) {
            // Add item.
            items[line[pos]]++;
            if (items.size() == TOKEN_LENGTH + 1) {
                std::cout << pos + 1 << std::endl;
                return 0;
            }
            // remove item.
            items[line[pos - TOKEN_LENGTH]]--;
            if (items[line[pos - TOKEN_LENGTH]] == 0) {
                items.erase(line[pos - TOKEN_LENGTH]);
            }
            
        }
    }
    std::cout << "NOT FOUND" << std::endl;
    
    return 0;
}
