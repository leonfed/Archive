#ifndef MYARCHIVE_UNARCHIVE_H
#define MYARCHIVE_UNARCHIVE_H


#include "tree.h"
#include <vector>


struct unarchive {

    unarchive();
    
    ~unarchive();

    void build_tree(unsigned char* buf);

    void get_original(unsigned char* buf, int size_buf, std::vector<unsigned char>& decode);

private:
    void dfs_delete(Node*);
    int get_bit(unsigned char*, int);
    Node* dfs_build_tree(unsigned char*, int);

    Node* tree;
    Node* cur;
    int ind;
};

#endif
