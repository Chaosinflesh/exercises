// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <algorithm>
#include <fstream>
#include <iostream>

long get_fingerprint(std::string line) {
    long f = 0L;
    for (auto i = 0; i < line.length(); i++) {
        int prio = line[i] >= 'a' ? line[i] - 'a' : line[i] - 'A' + 26;
        f |= 1L << prio;
    }
    std::cout << std::hex << f << " " << std::dec;
    return f;
}

int get_priority(std::string line) {
    long a = 0, b = 0;
    auto l = line.length() / 2;
    for (auto i = 0; i < l; i++) {
        int prio1 = line[i] >= 'a' ? line[i] - 'a' : line[i] - 'A' + 26;
        int prio2 = line[i + l] >= 'a' ? line[i + l] - 'a' : line[i + l] - 'A' + 26;
        a |= 1L << prio1;
        b |= 1L << prio2;
    }
    long result = a & b;
    int loc = 0;
    while (result != 0) {
        result >>= 1;
        loc++;
    }
    std::cout << line << ": " << std::hex << a << " " << b << " " << result << std::dec << " " << loc << " " << std::endl;
    return loc;
}

int main(int argc, char* argv[]) {
    // input is hard-coded as input.
    std::ifstream input("input");

    int sum = 0;
    int badge_sum = 0;
    long badge = -1L;
    int c = 0;
    for (std::string line; std::getline(input, line);) {
        // A
        sum += get_priority(line);

        // B
        badge &= get_fingerprint(line);
        c = (c + 1) % 3;
        if (c == 0) {
            int loc = 0;
            std::cout << "BADGE: " << std:: hex << badge;
            while (badge != 0) {
                badge >>= 1;
                loc++;
            }
            std::cout << " " << std::dec << loc << std::endl;
            badge_sum += loc;
            badge = -1L;
        }
        
    }
    std::cout << "A: " << sum << "\tB: " << badge_sum << std::endl;
    
    return 0;
}
