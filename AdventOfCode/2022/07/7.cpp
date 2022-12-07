// Author: Neil Bradley
// Copyright: Neil Bradley
// License: All rights reserved.
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <regex>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::regex;
using std::regex_constants::match_default;
using std::regex_match;
using std::smatch;
using std::string;
using std::queue;

#define CHAR_STR( ch )      string(1, ch )
#define SHARE( type, ... )  std::make_shared< type >( type ( __VA_ARGS__ ))
#define SHARED( type )      std::shared_ptr< type >

class Node {
    public:
        SHARED(Node) parent = nullptr;
        long size = 0L;
        string name;
        bool is_dir;
        map<string, SHARED(Node)> nodes;

        Node(string name, bool is_dir, long size) : name(name), is_dir(is_dir), size(size) {}
        long get_size();
};


long Node::get_size() {
    long size = 0L;
    for (auto node: this->nodes) {
        if (node.second->is_dir) {
            size += node.second->get_size();
        } else {
            size += node.second->size;
        }
    }
    return size;
}


void debug(SHARED(Node) node, int d) {
    cout << string(d * 2, ' ') << node->name;
    if (node->is_dir) {
        cout << endl;
        for (auto n : node->nodes) {
            debug(n.second, d + 1);
        }
    } else {
        cout << " (" << node->size << ")" << endl;
    }
}


SHARED(Node) get_filesystem() {
    // input is hard-coded as input.
    ifstream input("input");
    regex file_reg("(\\d+) ([a-zA-Z.]+)");
    smatch sm;

    auto root = SHARE(Node, "/", true, 0L);
    auto current = root;

    for (std::string line; std::getline(input, line);) {
        std::cout << line << std::endl;
        if (line[0] == '$') {
            // Commands
            if ("$ cd /" == line) {
                cout << "Switching to rootdir" << endl;
                current = root;
                
            } else if ("$ cd .." == line) {
                cout << "Switching to parent" << endl;
                if (current->parent) {
                    current = current->parent;
                } else {
                    cout << "Already at root!" << endl;
                }
                
            } else if ("$ ls" == line) {
                // Do nothing, we don't care.
                
            } else {
                string target = line.substr(5);
                cout << "Switching to " << target << endl;
                current = current->nodes[target];
            }
            
        } else if (line[0] == 'd') {
            // Directory
            string dir_name = line.substr(4);
            cout << "Found directory " << dir_name << endl;
            auto dir = SHARE(Node, dir_name, true, 0L);
            dir->parent = current;
            current->nodes[dir_name] = dir;
            
        } else {
            // File
            regex_match(line, sm, file_reg, match_default);
            cout << "DEBUG " << sm[1] << " " << sm[2] << endl;
            long size = std::stol(sm[1]);
            string file_name = sm[2];
            cout << "Found file " << file_name << " (" << size << ")" << endl;
            auto file = SHARE(Node, file_name, false, size);
            current->nodes[file_name] = file;
        }
    }

    return root;
}


void part_a(SHARED(Node) root) {
    queue<SHARED(Node)> q;
    q.push(root);

    long total = 0L;
    while (q.size() > 0) {
        auto node = q.front();
        long t = node->get_size();
        cout << node->name << ": " << t;
        if (t < 100'000) {
            total += t;
            cout << " YES";
        }
        cout << endl;
        for (auto n : node->nodes) {
            if (n.second->is_dir) {
                q.push(n.second);
            }
        }
        q.pop();
    }
    cout << "A: " << total << endl;
}


void part_b(SHARED(Node) root) {
    long limit = root->get_size() - 40'000'000L;
    cout << endl << "LIMIT=" << limit << endl;

    long smallest = root->get_size();
    queue<SHARED(Node)> q;
    q.push(root);

    long total = 0L;
    while (q.size() > 0) {
        auto node = q.front();
        long t = node->get_size();
        cout << node->name << ": " << t;
        if (t >= limit && t < smallest) {
            smallest = t;
            cout << " YES";
        }
        cout << endl;
        for (auto n : node->nodes) {
            if (n.second->is_dir) {
                q.push(n.second);
            }
        }
        q.pop();
    }
    cout << "B: " << smallest << endl;
}


int main(int argc, char* argv[]) {
    
    auto root = get_filesystem();
    debug(root, 0);
    part_a(root);
    part_b(root);
    
    return 0;
}
