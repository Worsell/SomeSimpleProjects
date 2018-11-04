//
// Created by Ivan Korotkii on 31/10/2018.
//

#include <gtest/gtest.h>
#include <BTree.h>

using namespace tree;

TEST(BTree, BtreeTestSimpleAdd) {
    BTree<int> bTree = BTree<int>(2);
    ASSERT_TRUE(bTree.insert(12));
    ASSERT_TRUE(bTree.insert(13));
    ASSERT_TRUE(bTree.insert(234));
    ASSERT_TRUE(bTree.insert(232));
    ASSERT_TRUE(bTree.insert(546));
    ASSERT_TRUE(bTree.insert(238));
    ASSERT_TRUE(bTree.insert(231));
    ASSERT_TRUE(bTree.insert(435));
    ASSERT_TRUE(bTree.insert(54));
}


TEST(BTree, BtreeTestSimpleRemove) {

    BTree<int> bTree = BTree<int>(2);
    bTree.insert(12);
    bTree.insert(13);
    bTree.insert(234);
    ASSERT_TRUE(bTree.search(234));
    bTree.insert(232);
    ASSERT_TRUE(bTree.search(232));
    bTree.insert(546);
    ASSERT_FALSE(bTree.search(1));
    ASSERT_TRUE(bTree.search(234));
    bTree.insert(238);
    bTree.insert(231);
    bTree.insert(435);
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));


    ASSERT_TRUE(bTree.search(435));
    bTree.insert(54);
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(12));
    bTree.remove(12);
    ASSERT_FALSE(bTree.search(12));
    bTree.remove(13);
    ASSERT_FALSE(bTree.search(13));
    ASSERT_TRUE(bTree.search(546));
    bTree.remove(546);
    ASSERT_FALSE(bTree.search(546));
    ASSERT_TRUE(bTree.search(54));
    bTree.insert(54);
    ASSERT_FALSE(bTree.search(54));

}


TEST(BTree, BtreeSimpleSearch) {
    BTree<int> bTree = BTree<int>(2);
    ASSERT_FALSE(bTree.search(1));
    bTree.insert(12);
    ASSERT_TRUE(bTree.search(12));
    bTree.insert(13);
    ASSERT_TRUE(bTree.search(13));
    bTree.insert(234);
    ASSERT_TRUE(bTree.search(234));
    bTree.insert(232);
    ASSERT_TRUE(bTree.search(232));
    bTree.insert(546);
    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));

    bTree.insert(238);
    ASSERT_TRUE(bTree.search(238));
    bTree.insert(231);
    ASSERT_TRUE(bTree.search(12));

    ASSERT_TRUE(bTree.search(231));
    bTree.insert(435);
    ASSERT_TRUE(bTree.search(12));

    ASSERT_TRUE(bTree.search(435));
    bTree.insert(54);
    ASSERT_FALSE(bTree.search(1));
    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));
    ASSERT_TRUE(bTree.search(238));
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(435));

}


TEST(BTree, BtreeCommon) {
    BTree<int> bTree = BTree<int>(2);
    ASSERT_FALSE(bTree.search(1));
    bTree.insert(12);
    ASSERT_TRUE(bTree.search(12));
    bTree.insert(13);
    ASSERT_TRUE(bTree.search(13));
    bTree.remove(12);
    ASSERT_FALSE(12);
    ASSERT_TRUE(bTree.search(13));
    bTree.insert(234);
    ASSERT_TRUE(bTree.search(234));
    bTree.insert(232);
    ASSERT_TRUE(bTree.search(232));
    bTree.remove(232);
    ASSERT_FALSE(232);
    bTree.insert(546);
    ASSERT_TRUE(bTree.search(546));
    bTree.insert(238);
    ASSERT_TRUE(bTree.search(238));
    bTree.insert(231);
    ASSERT_TRUE(bTree.search(231));
    bTree.insert(435);
    ASSERT_TRUE(bTree.search(435));
    bTree.insert(54);
    ASSERT_FALSE(bTree.search(1));
    ASSERT_TRUE(bTree.search(54));
    bTree.remove(54);
    ASSERT_FALSE(bTree.search(54));
    ASSERT_TRUE(bTree.search(435));
    bTree.remove(435);
    ASSERT_FALSE(bTree.search(435));
    ASSERT_TRUE(bTree.search(231));
    bTree.remove(231);
    ASSERT_FALSE(bTree.search(231));
    ASSERT_TRUE(bTree.search(238));
    bTree.remove(238);
    ASSERT_FALSE(bTree.search(238));
    ASSERT_TRUE(bTree.search(546));
    bTree.remove(546);
    ASSERT_FALSE(bTree.search(546));
    ASSERT_TRUE(bTree.search(234));
    bTree.remove(234);
    ASSERT_FALSE(bTree.search(234));
    ASSERT_TRUE(bTree.search(13));
    bTree.remove(13);
    ASSERT_FALSE(bTree.search(13));

}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
