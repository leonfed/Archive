#include <iostream>
#include <fstream>
#include <string>
#include "my_lib/archive.h"
#include "my_lib/unarchive.h"

using namespace std;

const int size_buf = 4000000;

void do_archive(string& input, string& output) {
    ifstream in(input, ios::binary);
    ifstream in2(input, ios::binary);
    if (!in) {
        cerr << "Can't open file";
        in.close();
        return;
    }
    ofstream out(output, ios::binary);
    unsigned char buf[size_buf];
    archive arch;
    do {
        in.read((char *)buf, sizeof(buf));
        arch.count(buf, (int)in.gcount());
    } while (in);
    arch.generate_code();
    vector<unsigned char> code_char;
    arch.get_tree_code(code_char);
    out.write((char *)code_char.data(), code_char.size());
    code_char.clear();
    do {
        in2.read((char *)buf, sizeof(buf));
        arch.get_data_code(buf, (int)in2.gcount(), code_char);
        out.write((char *)code_char.data(), code_char.size());
        code_char.clear();
    } while (in2);
    in.close();
    in2.close();
    out.close();
}

void do_unarchive(string& input, string& output) {
    ifstream in(input, ios::binary);
    if (!in) {
        cerr << "Can't open file";
        in.close();
        return;
    }
    ofstream out(output, ios::binary);
    unsigned char buf[size_buf];
    in.read((char *)buf, sizeof(buf));
    unarchive unarch;
    try {
        unarch.build_tree(buf);
    } catch(...) {
        cerr << "Incorrect data";
        in.close();
        out.close();
        return;
    }
    vector<unsigned char> data;
    try {
         unarch.get_original(buf, static_cast<int>(in.gcount()), data);
    } catch(...) {
        cerr << "Incorrect data";
        in.close();
        out.close();
        return;
    }
    out.write((char *)data.data(), data.size());
    data.clear();
    while (in) {
        in.read((char *)buf, sizeof(buf));
        try {
            unarch.get_original(buf, static_cast<int>(in.gcount()), data);
        } catch(...) {
            cerr << "Incorrect data";
            in.close();
            out.close();
            return;
        }
        out.write((char *)data.data(), data.size());
        data.clear();
    }
    in.close();
    out.close();
}

int main() {
    char command;
    string input, output;
    cin >> command >> input >> output;
    if (command == 'c') {
        do_archive(input, output);
    } else if (command == 'd') {
        do_unarchive(input, output);
    }
    return 0;
}
