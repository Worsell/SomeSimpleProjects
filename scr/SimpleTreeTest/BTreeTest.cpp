//
// Created by Ivan Korotkii on 31/10/2018.
//

#include <gtest/gtest.h>
#include <BTree.h>
#include <SmartBTree.h>
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
    // bTree.print();
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
    bTree.insert(54);

    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));
    ASSERT_TRUE(bTree.search(238));
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(435));
    ASSERT_TRUE(bTree.search(54));

    // bTree.print();
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
    bTree.remove(54);
    ASSERT_FALSE(bTree.search(54));
    ASSERT_TRUE(bTree.search(435));
    bTree.remove(435);
    ASSERT_FALSE(bTree.search(435));
    bTree.remove(232);
    bTree.remove(238);
    bTree.remove(234);
    bTree.remove(231);
    ASSERT_FALSE(bTree.search(232));
    ASSERT_FALSE(bTree.search(238));
    ASSERT_FALSE(bTree.search(231));
    ASSERT_FALSE(bTree.search(234));

    ASSERT_TRUE(bTree.size()==0);

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
    bTree.insert(54);
    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));
    ASSERT_TRUE(bTree.search(238));
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(435));
    ASSERT_TRUE(bTree.search(54));

    ASSERT_TRUE(bTree.remove(54));
    ASSERT_FALSE(bTree.search(54));

    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(232));
    ASSERT_TRUE(bTree.search(546));
    ASSERT_TRUE(bTree.search(238));
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(435));

    ASSERT_TRUE(bTree.remove(232));
    ASSERT_FALSE(bTree.search(232));
    ASSERT_TRUE(bTree.search(12));
    ASSERT_TRUE(bTree.search(13));
    ASSERT_TRUE(bTree.search(234));
    ASSERT_TRUE(bTree.search(546));
    ASSERT_TRUE(bTree.search(238));
    ASSERT_TRUE(bTree.search(231));
    ASSERT_TRUE(bTree.search(435));

}


TEST(BTree, BtreeSimpleSearch) {
    BTree<int> bTree = BTree<int>(4);
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
    //  bTree.print();
}
TEST(BTree, BtreeTestHard) {
    BTree<int> bTree = BTree<int>(5);
    for (int x = 1; x < 1000; x++) {
        bTree.insert(x);
        bTree.search(x);
    }
    for (int x = 1000; x >= 1; x--) {
        bTree.search(x);
    }
    for (int x = 1; x < 1000; x++) {
        ASSERT_TRUE(bTree.search(x));
        bTree.remove(x);
        ASSERT_FALSE(bTree.search(x));
    }
    ASSERT_TRUE(bTree.size()==0);

    // bTree.print();
}





TEST(SmartBTree, BtreeCommon) {
    SmartBTree<int, std::string> bTree = SmartBTree<int, std::string>(5, 5, 2, true);
    std::string one = "one";
    std::string two = "two";
    std::string tree = "tree";
    std::string four = "four";
    std::string five = "five";
    std::string six = "six";
    std::string seven = "seven";
    std::string eight = "eight";
    std::string nine = "nine";
    std::string ten = "ten";
    ASSERT_TRUE(bTree.add(12, one));
    ASSERT_TRUE(bTree.add(13, two));
    ASSERT_TRUE(bTree.add(234, tree));
    ASSERT_TRUE(bTree.add(232, four));
    ASSERT_TRUE(*bTree.search(12) == one);
    ASSERT_TRUE(*bTree.search(13) == two);
    ASSERT_TRUE(*bTree.search(232) == four);
    ASSERT_TRUE(*bTree.search(234) == tree);
    ASSERT_TRUE(*bTree.search(13) == two);
    bTree.setLazy(false);
    ASSERT_FALSE(bTree.add(546, five));
    ASSERT_FALSE(bTree.add(238, six));
    ASSERT_FALSE(bTree.add(231, seven));
    ASSERT_TRUE(bTree.search(546) == nullptr);
    ASSERT_TRUE(bTree.search(238) == nullptr);
    ASSERT_TRUE(bTree.search(231) == nullptr);
    bTree.force();
    ASSERT_TRUE(*bTree.search(546) == five);
    ASSERT_TRUE(*bTree.search(238) == six);
    ASSERT_TRUE(*bTree.search(231) == seven);

    ASSERT_TRUE(*bTree.search(12) == one);
    ASSERT_TRUE(*bTree.search(13) == two);
    ASSERT_TRUE(*bTree.search(232) == four);
    ASSERT_TRUE(*bTree.search(234) == tree);
    ASSERT_TRUE(*bTree.search(13) == two);
    ASSERT_TRUE(*bTree.search(546) == five);
    ASSERT_TRUE(*bTree.search(238) == six);
    ASSERT_TRUE(*bTree.search(231) == seven);
    bTree.setLazy(true);
    bTree.add(54, nine);
    bTree.add(435, ten);
    ASSERT_TRUE(*bTree.search(54) == nine);
    ASSERT_TRUE(*bTree.search(435) == ten);
    ASSERT_TRUE(bTree.remove(54));
    ASSERT_TRUE(bTree.remove(232));
    ASSERT_TRUE(*bTree.search(12) == one);
    ASSERT_TRUE(*bTree.search(13) == two);
    ASSERT_TRUE(*bTree.search(234) == tree);
    ASSERT_TRUE(*bTree.search(13) == two);
    ASSERT_TRUE(*bTree.search(546) == five);
    ASSERT_TRUE(*bTree.search(238) == six);
    ASSERT_TRUE(*bTree.search(231) == seven);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
