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
    std::regex reg("move (\\d+) from (\\d+) to (\\d+)");
    std::smatch sm;

    bool loading = true;
    std::deque<char> dockA[9];    // Sadly, I read this in the data. I could've made it calculated, but nah.
    std::deque<char> dockB[9];    // Sadly, I read this in the data. I could've made it calculated, but nah.
    for (std::string line; std::getline(input, line);) {
        if (loading) {
            if (line.empty()) {
                loading = false;
                continue;
            }
            if (line[1] == '1') {
                continue;
            }
            for (int i = 0; i < 9; i++) {
                if (line[i * 4 + 1] != ' ') {
                    dockA[i].push_back(line[i * 4 + 1]);
                    dockB[i].push_back(line[i * 4 + 1]);
                }
            }
        } else {
            // Perform the operation.
            std::regex_match(line, sm, reg, std::regex_constants::match_default);
            int count = std::stod(sm[1]);
            int from = std::stod(sm[2]) - 1;
            int to = std::stod(sm[3]) - 1;
            std::deque<char> crane;
            for (int i = 0; i < count; i++) {
                dockA[to].push_front(dockA[from].front());
                dockA[from].pop_front();
                crane.push_front(dockB[from].front());
                dockB[from].pop_front();
            }
            for (auto c : crane) {
                dockB[to].push_front(c);
            }
        }
    }

    for (auto d: dockA) {
        std::cout << d.front();
    }
    std::cout << std::endl;
    for (auto d: dockB) {
        std::cout << d.front();
    }
    std::cout << std::endl;
    
    return 0;
}
