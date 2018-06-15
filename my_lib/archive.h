#ifndef MYARCHIVE_ARCHIVE_H
#define MYARCHIVE_ARCHIVE_H

#include <iostream>
#include <vector>
#include "tree.h"

struct archive {
    archive()
            : cnt(256, 0)
            , byte_code(256)
    {}

    ~archive();

    void count(unsigned char* buf, int size_buf);
    void generate_code();
    void get_tree_code(std::vector<unsigned char>& code);
    void get_data_code(unsigned char* buf, int size_buf, std::vector<unsigned char>& code);


private:
    void dfs_delete(Node*);
    void dfs_fill_byte_code(std::pair<unsigned long long, int>&, Node*);
    void convert_bool_to_char(std::vector<bool>&, std::vector<unsigned char>&);
    void convert_long_to_char(std::vector<std::pair<unsigned long long, int>>&, std::vector<unsigned char>&);

    std::vector<unsigned long long> cnt;
    Node* tree;
    std::vector<std::pair<unsigned long long, int>> byte_code;
    std::pair<unsigned long long, int> final_byte;
};

#endif
