#ifndef MYARCHIVE_UNARCHIVE_H
#define MYARCHIVE_UNARCHIVE_H


#include "tree.h"
#include <vector>


struct unarchive {

    unarchive();

    //build huffman tree
    void build_tree(unsigned char* buf);

    //write original data to vector<unsigned char>decode
    void get_original(unsigned char* buf, int size_buf, std::vector<unsigned char>& decode);

    //check_correctness of input data
    bool check_correctness();

private:
    int get_bit(unsigned char* buf, int index);
    std::shared_ptr<Node> dfs_build_tree(unsigned char* buf, int length);

    std::shared_ptr<Node> tree;
    std::shared_ptr<Node> cur;
    int ind;
    bool last_symbol_is_final;
    unsigned char check_xor, cur_xor;
};

#endif