#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <string>

#include "my_lib/archive.h"
#include "my_lib/unarchive.h"
#include "gtest/gtest.h"

std::vector<unsigned char> do_archive(std::vector<unsigned char>& orig) {
    std::vector<unsigned char> code;
    archive arch;
    arch.count(orig.data(), static_cast<int>(orig.size()));
    arch.generate_code();
    arch.get_tree_code(code);
    arch.get_data_code(orig.data(), static_cast<int>(orig.size()), code);
    return code;
}

std::vector<unsigned char> do_unarchive(std::vector<unsigned char>& code) {
    std::vector<unsigned char> decode;
    unarchive unarch;
    unarch.build_tree(code.data());
    unarch.get_original(code.data(), code.size(), decode);
    return decode;
}

TEST(correctness, null) {
    std::string test_string;
    std::vector<unsigned char> orig(test_string.begin(), test_string.end());
    std::vector<unsigned char> code = do_archive(orig);
    std::vector<unsigned char> decode = do_unarchive(code);
    EXPECT_EQ(orig, decode);
}

TEST(correctness, one_letter) {
    std::string test_string = "a";
    std::vector<unsigned char> orig(test_string.begin(), test_string.end());
    std::vector<unsigned char> code = do_archive(orig);
    std::vector<unsigned char> decode = do_unarchive(code);
    EXPECT_EQ(orig, decode);
}

TEST(correctness, few_letter) {
    std::string test_string = "qwertyqwerty";
    std::vector<unsigned char> orig(test_string.begin(), test_string.end());
    std::vector<unsigned char> code = do_archive(orig);
    std::vector<unsigned char> decode = do_unarchive(code);
    EXPECT_EQ(orig, decode);
}

