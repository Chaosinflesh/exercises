// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>

using std::string;
using std::tuple;

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    int santa_x = 0;
    int santa_y = 0;
    int robot_x = 0;
    int robot_y = 0;
    std::set<tuple<int, int>> delivered;
    tuple<int, int> start(0, 0);
    delivered.emplace(start);

    string line;
    std::getline(input, line);

    bool santa = true;
    for (auto l : line) {
        int diff_x, diff_y;
        switch (l) {
            case '<': diff_x = -1; break;
            case '^': diff_y = -1; break;
            case '>': diff_x =  1; break;
            case 'v': diff_y =  1; break;
        }
        tuple<int, int> t;
        if (santa) {
            santa_x += diff_x;
            santa_y += diff_y;
            t.first = santa_x;
            t.second = santa_y;
        } else {
            robot_x += diff_x;
            robot_y += diff_y;
            t.first = robot_x;
            t.second = robot_y;
        }
        auto it = delivered.find(t);
        if (it != delivered.end()) {
            it->second++;
        } else {
            delivered.emplace(t);
        }
    }
    
    std::cout << "A: " << delivered.size() << "\tB: " << std::endl;

    return 0;
}
