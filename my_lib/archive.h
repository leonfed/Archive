#ifndef MYARCHIVE_ARCHIVE_H
#define MYARCHIVE_ARCHIVE_H

#include <iostream>
#include <vector>
#include <debug/vector>
#include "tree.h"

struct archive {
    archive();

    //count symbols and check_xor
    void count(unsigned char* buf, int size_buf);

    //generate huffman tree
    void generate_code();

    //write code of tree to vector<unsigned char>code
    void get_tree_code(std::vector<unsigned char>& code);

    //write code of buf to vector<unsigned char>code
    void get_data_code(unsigned char* buf, int size_buf, std::vector<unsigned char>& code);


private:
    void dfs_fill_byte_code(std::pair<unsigned long long, int>& , std::shared_ptr<Node>);
    void convert_bool_to_char(std::vector<bool>& code_bool, std::vector<unsigned char>& code_char);
    void convert_long_to_char(std::vector<std::pair<unsigned long long, int>>& code_long, std::vector<unsigned char>& code_char);

    std::vector<unsigned long long> cnt;
    std::shared_ptr<Node> tree;
    std::vector<std::pair<unsigned long long, int>> byte_code;
    std::pair<unsigned long long, int> final_byte;
};

#endif
