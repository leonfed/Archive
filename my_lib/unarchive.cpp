#include <vector>
#include <stdexcept>
#include "tree.h"
#include "unarchive.h"

void unarchive::dfs_delete(Node* root) {
    if (root->left) {
        dfs_delete(root->left);
        dfs_delete(root->right);
    }
    delete root;
}

unarchive::~unarchive() {
    if (tree) {
        dfs_delete(tree);
    }
}

int unarchive::get_bit(unsigned char* a, int i) {
    int ans;
    try {
        int k = i / 8, t = 7 - i % 8;
        ans = (a[k] >> t) & 1;
    } catch(...) {
        throw std::runtime_error("");
    }
    return ans;
}

Node* unarchive::dfs_build_tree(unsigned char* buf) {
    Node* root = new Node{ 1, nullptr, nullptr, 0 };
    if (get_bit(buf, (int)ind++)) {
        if (get_bit(buf, (int)ind++)) {
            root->count = 0;
        } else {
            unsigned char pow = 1;
            for (int i = 0; i < 8; i++) {
                root->byte += pow * get_bit(buf, i + (int)ind);
                pow <<= 1;
            }
            ind += 8;
        }
    } else {
        root->left = dfs_build_tree(buf);
        root->right = dfs_build_tree(buf);
    }
    return root;
}

void unarchive::build_tree(unsigned char *buf) {
    cur = tree = dfs_build_tree(buf);
    if (ind % 8 != 0) {
        ind += (8 - ind % 8);
    }
}

void unarchive::get_original(unsigned char* buf, unsigned long long input_size, std::vector<unsigned char>& orig) {
    input_size = input_size * 8 - ind;
    unsigned long long i = 0;
    for (; i < input_size; i++) {
        if (get_bit(buf, (int)ind++)) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
        if (!cur->left) {
            if (cur->count != 0) {
                orig.push_back(cur->byte);
            } else {
                if (ind % 8 != 0) {
                    i += (8 - ind % 8);
                    ind += (8 - ind % 8);
                }
            }
            cur = tree;
        }
    }
    ind = 0;
}