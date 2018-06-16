#ifndef MYARCHIVE_UNARCHIVE_H
#define MYARCHIVE_UNARCHIVE_H


#include "tree.h"
#include <vector>


struct unarchive {

    unarchive();

    void build_tree(unsigned char* buf);

    void get_original(unsigned char* buf, int size_buf, std::vector<unsigned char>& decode);

private:
    int get_bit(unsigned char* buf, int index);
    std::shared_ptr<Node> dfs_build_tree(unsigned char* buf, int length);

    std::shared_ptr<Node> tree;
    std::shared_ptr<Node> cur;
    int ind;
};

#endif