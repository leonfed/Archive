#include <vector>
#include <stdexcept>
#include "tree.h"
#include "unarchive.h"

unarchive::unarchive()
        : tree(nullptr)
        , cur(nullptr)
        , ind(0)
{}

void unarchive::dfs_delete(Node* root) {
    if (!tree) {
        return;
    }
    if (root->left) {
        dfs_delete(root->left);
    }
    if (root->right) {
        dfs_delete(root->right);
    }
    delete root;
}

unarchive::~unarchive() {
    dfs_delete(tree);
}

int unarchive::get_bit(unsigned char* a, int i) {
    int ans;
    try {
        int k = i / 8, t = 7 - i % 8;
        ans = (a[k] >> t) & 1;
    } catch(...) {
        throw std::runtime_error("incorrect data");
    }
    return ans;
}

Node* unarchive::dfs_build_tree(unsigned char* buf, int length) {
    if (length > 64) {
        return nullptr;
    }
    Node* root = new Node{ 1, nullptr, nullptr, 0 };
    if (get_bit(buf, ind++)) {
        if (get_bit(buf, ind++)) {
            root->count = 0;
        } else {
            unsigned char pow = 1;
            for (int i = 0; i < 8; i++) {
                root->byte += pow * get_bit(buf, i + ind);
                pow <<= 1;
            }
            ind += 8;
        }
    } else {
        root->left = dfs_build_tree(buf, length + 1);
        if (!root->left) {
            dfs_delete(root);
            return nullptr;
        }
        root->right = dfs_build_tree(buf, length + 1);
        if (!root->right) {
            dfs_delete(root);
            return nullptr;
        }
    }
    return root;
}

void unarchive::build_tree(unsigned char *buf) {
    cur = tree = dfs_build_tree(buf, 0);
    if (!tree) {
        throw std::runtime_error("incorrect dara");
    }
    if (ind % 8 != 0) {
        ind += (8 - ind % 8);
    }
}

void unarchive::get_original(unsigned char* buf, int input_size, std::vector<unsigned char>& orig) {
    input_size = input_size * 8 - ind;
    int i = 0;
    for (; i < input_size; i++) {
        if (get_bit(buf, ind++)) {
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
