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
    arch.get_tree_code_and_check_xor(code_char);
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
    } catch(std::runtime_error& e) {
        cerr << e.what();
        in.close();
        out.close();
        return;
    }
    vector<unsigned char> data;
    try {
         unarch.get_original(buf, static_cast<int>(in.gcount()), data);
    } catch(std::runtime_error& e) {
        cerr << e.what();
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
        } catch(std::runtime_error& e) {
            cerr << e.what();
            in.close();
            out.close();
            return;
        }
        out.write((char *)data.data(), data.size());
        data.clear();
    }
    if (!unarch.check_correctness()) {
        cerr << "Incorrect data";
    }
    in.close();
    out.close();
}

int main(int argc, char **argv) {
    char c;
    string input, output;
    try {
        c = *argv[1];
        input = string(argv[2]);
        output = string(argv[3]);
    } catch(...) {
        cerr << "incorrect command";
        return 0;
    }
    if (c == 'c') {
        do_archive(input, output);
    } else if (c == 'd') {
        do_unarchive(input, output);
    } else {
        cerr << "incorrect command";
    }
    return 0;
}
