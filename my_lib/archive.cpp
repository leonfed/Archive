#include "archive.h"
#include <fstream>
#include <iostream>
#include <set>

void archive::dfs_delete(Node* root) {
    if (root->left) {
        dfs_delete(root->left);
        dfs_delete(root->right);
    }
    delete root;
}

archive::~archive() {
    if (tree) {
        dfs_delete(tree);
    }
}

void archive::count(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        cnt[data[i]]++;
    }
}

void archive::dfs_fill_byte_code(std::pair<unsigned long long, int>& cur_code, Node* v) {
    if (v->left) {
        cur_code = {cur_code.first * 2, cur_code.second + 1};
        dfs_fill_byte_code(cur_code, v->left);
        cur_code.first++;
        dfs_fill_byte_code(cur_code, v->right);
        cur_code = {cur_code.first / 2, cur_code.second - 1};
    } else {
        if (v->count != 0) {
            byte_code[v->byte] = cur_code;
        } else {
            final_byte = cur_code;
        }
    }
}

void archive::generate_code() {
    auto cmp = [](Node* a, Node* b) { return a->count < b->count; };
    std::multiset<Node*, decltype(cmp)> nd(cmp);
    nd.insert(new Node{ 0, nullptr, nullptr, 0 });
    for (int i = 0; i < 256; i++) {
        if (cnt[i] != 0) {
            nd.insert(new Node{ cnt[i], nullptr, nullptr, (unsigned char)i });
        }
    }
    while (nd.size() > 1) {
        Node *min1 = *nd.begin();
        nd.erase(nd.begin());
        Node *min2 = *nd.begin();
        nd.erase(nd.begin());
        nd.insert(new Node{ min1->count + min2->count, min1, min2, 0 });
    }
    tree = *nd.begin();
    std::pair<unsigned long long, int> cur_code;
    dfs_fill_byte_code(cur_code, tree);
}

void dfs_get_tree_code(std::vector<bool>& code, Node* v) {
    if (v->left) {
        code.push_back(0);
        dfs_get_tree_code(code, v->left);
        dfs_get_tree_code(code, v->right);
    } else {
        code.push_back(1);
        code.push_back(v->count == 0);
        if (v->count > 0) {
            unsigned char byte = v->byte;
            for (int i = 0; i < 8; i++) {
                code.push_back(static_cast<bool>(byte & 1));
                byte >>= 1;
            }
        }
    }
}

void archive::convert_bool_to_char(std::vector<bool>& code_vector, std::vector<unsigned char>& code_char) {
    int sz = (int)code_vector.size() / 8;
    unsigned char cur;
    for (int i = 0; i < sz * 8; i += 8) {
        cur = 0;
        for (int j = 0; j < 8; j++) {
            cur = cur * 2 + code_vector[i + j];
        }
        code_char.push_back(cur);
    }
    if (code_vector.size() % 8 != 0) {
        cur = 0;
        for (int j = (int)code_vector.size() % 8; j > 0; j--) {
            cur = cur * 2 + code_vector[code_vector.size() - j];
        }
        cur <<= (8 - code_vector.size() % 8);
        code_char.push_back(cur);
    }
}

void archive::get_tree_code(std::vector<unsigned char>& code_char) {
    std::vector<bool> code;
    dfs_get_tree_code(code, tree);
    convert_bool_to_char(code, code_char);
}

void archive::get_data_code(unsigned char* data, int length, std::vector<unsigned char>& code_char) {
    std::vector<std::pair<unsigned long long, int>> code_vector;
    for (int i = 0; i < length; i++) {
        code_vector.push_back(byte_code[data[i]]);
    }
    code_vector.push_back(final_byte);
    convert_long_to_char(code_vector, code_char);
}



void archive::convert_long_to_char(std::vector<std::pair<unsigned long long, int>>& code_vector, std::vector<unsigned char>& code_char) {
    int rest = 8;
    unsigned char cur = 0;
    for (std::pair<unsigned long long, int> p : code_vector) {
        unsigned long long num = p.first;
        int cnt = p.second;
        while (cnt >= rest) {
            cur <<= rest;
            cur += (num >> (cnt - rest));
            code_char.push_back(cur);
            cnt -= rest;
            num &= (1 << (cnt + 1)) - 1;
            rest = 8;
            cur = 0;
        }
        if (cnt > 0) {
            cur <<= cnt;
            cur += num;
            rest -= cnt;
        }
    }
    if (rest > 0 && rest != 8) {
        cur <<= rest;
        code_char.push_back(cur);
    }
}
