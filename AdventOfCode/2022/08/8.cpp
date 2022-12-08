// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<string> map;
vector<string> visible;

int max_x;
int max_y;

void check_east_west() {
    for (int y = 1; y < max_y - 1; y++) {
        int h_w = map[y][0];
        int h_e = map[y][max_x - 1];
        for (int x = 1; x < max_x - 1; x++) {
            char h = map[y][x];
            if (h > h_w) {
                h_w = h;
                visible[y][x] = h;
            }
            h = map[y][max_x - x - 1];
            if (h > h_e) {
                h_e = h;
                visible[y][max_x - x - 1] = h;
            }
        }
    }
}

void check_north_south() {
    for (int x = 1; x < max_x - 1; x++) {
        int h_n = map[0][x];
        int h_s = map[max_y - 1][x];
        for (int y = 1; y < max_y - 1; y++) {
            char h = map[y][x];
            if (h > h_n) {
                h_n = h;
                visible[y][x] = h;
            }
            h = map[max_y - y - 1][x];
            if (h > h_s) {
                h_s = h;
                visible[max_y - y - 1][x] = h;
            }
        }
    }
}


long get_view(int y, int x, int o_x, int o_y) {
    long count = 0;
    char h = map[y][x];
    x += o_x;
    y += o_y;
    while (x >= 0 && x < max_x && y >= 0 && y < max_y) {
        if (map[y][x] >= h) {
            count++;
            break;
        }
        count++;
        x += o_x;
        y += o_y;
    }
    return count;
}


long get_view_score(int y, int x) {
    //cout << y << "," << x << " " << map[y][x] << ": ";
    long w = get_view(y, x, -1,  0);
    long e = get_view(y, x,  1,  0);
    long n = get_view(y, x,  0, -1);
    long s = get_view(y, x,  0,  1);
    long total = w * e * n * s;
    //cout << w << " " << e << " " << n << " " << s << " -> " << total << endl;
    return total;
}


int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    for (std::string line; std::getline(input, line);) {
        map.push_back(line);
        visible.push_back(string(line.length(), ' '));
    }
    max_x = map.size();
    max_y = map[0].length();

    check_east_west();
    check_north_south();

    int a = 2 * (max_x + max_y) - 4;
    for (auto v : visible) {
        for (char t : v) {
            if (t != ' ') {
                a++;
            }
        }
        //cout << v << endl;
    }

    int b = 0;
    for (int y = 0; y < max_y; y++) {
        for (int x = 0; x < max_x; x++) {
            int score = get_view_score(y, x);
            if (score > b) {
                b = score;
            }
        }
    }

    cout << "A: " << a << "\tB: " << b <<endl;
    
    return 0;
}
