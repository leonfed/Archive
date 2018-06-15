#ifndef MYARCHIVE_UNARCHIVE_H
#define MYARCHIVE_UNARCHIVE_H


#include "tree.h"
#include <vector>


struct unarchive {

    unarchive()
            : ind(0)
    {}
    
    ~unarchive();

    void build_tree(unsigned char*);

    void get_original(unsigned char*, unsigned long long, std::vector<unsigned char>&);

private:
    void dfs_delete(Node*);
    int get_bit(unsigned char*, int);
    Node* dfs_build_tree(unsigned char*);

    Node* tree;
    Node* cur;
    int ind;
};

#endif
