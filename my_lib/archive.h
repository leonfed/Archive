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

    void count(unsigned char *, int);
    void generate_code();
    void  get_tree_code(std::vector<unsigned char>&);
    void get_data_code(unsigned char*, int, std::vector<unsigned char>&);


private:
    void dfs_delete(Node*);
    void dfs_fill_byte_code(std::vector<bool>&, Node*);
    void convert_to_char(std::vector<bool>& code_vector, std::vector<unsigned char>&);

    std::vector<unsigned long long> cnt;
    Node* tree;
    std::vector<std::vector<bool>> byte_code;
    std::vector<bool> final_byte;
};

#endif
