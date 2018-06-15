#ifndef MYARCHIVE_TREE_H
#define MYARCHIVE_TREE_H

struct Node {
    unsigned long long count;
    Node *left, *right;
    unsigned char byte;
};

#endif
