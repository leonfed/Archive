#ifndef MYARCHIVE_ARCHIVE_H
#define MYARCHIVE_ARCHIVE_H

#include <iostream>
#include <vector>
#include <debug/vector>
#include "tree.h"

struct archive {
    archive();

    void count(unsigned char* buf, int size_buf);
    void generate_code();
    void get_tree_code(std::vector<unsigned char>& code);
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
