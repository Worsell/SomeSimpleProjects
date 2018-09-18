//
// Created by Ivan Korotkii on 09/09/2018.
//

#include <gtest/gtest.h>
#include "../SimpleTree/SimpleSearchTree.h"

TEST(SimpleSearchTree, SimepleInsertAndContainsTest) {
    auto *tree = new ::myLibrary::SimpleSearchTree<int>();
    ASSERT_EQ(false, tree->contains(5));
    ASSERT_EQ(false, tree->contains(5));
    ASSERT_EQ(false, tree->contains(5));
    tree->insert(10);
    ASSERT_EQ(true, tree->contains(10));
    tree->insert(15);
    ASSERT_EQ(false, tree->contains(5));
    tree->insert(3);
    ASSERT_EQ(true, tree->contains(3));
    tree->insert(8);
    ASSERT_EQ(true, tree->contains(8));
    tree->insert(2);
    ASSERT_EQ(false, tree->contains(5));
    tree->insert(4);
    ASSERT_EQ(true, tree->contains(4));
    tree->insert(11);
    ASSERT_EQ(false, tree->contains(5));
}


TEST(Node, SimpleRemoveNode) {
    //auto *d = new ::myLibrary::Node<int>(11, nullptr, nullptr, nullptr);
    //auto *d1 = new ::myLibrary::Node<int>(9, nullptr, nullptr, nullptr);
    //auto *d2 = new ::myLibrary::Node<int>(10, d1, nullptr, d);
}


TEST(SimpleSearchTree, SimpleAddAll) {
    auto *test = new std::vector<int>();
    auto *const trees = new ::myLibrary::SimpleSearchTree<int>();

    test->reserve(5);

    test->push_back(1);
    test->push_back(2);
    test->push_back(3);
    test->push_back(4);
    test->push_back(5);

    trees->insertAll(test->begin(), test->end());
    ASSERT_EQ(true, trees->contains(1));
    ASSERT_EQ(true, trees->contains(2));
    ASSERT_EQ(true, trees->contains(3));
    ASSERT_EQ(true, trees->contains(4));
    ASSERT_EQ(true, trees->contains(5));
}

TEST(SimpleSearchTree, SimpleRemove) {
    auto *const trees = new ::myLibrary::SimpleSearchTree<int>();
    trees->insert(1);
    trees->insert(2);
    trees->insert(3);
    trees->insert(4);
    ASSERT_EQ(trees->remove(4), true);
    ASSERT_EQ(trees->remove(2), true);
}

TEST(SimpleSearchTree, SpeedOfManyInsert) {
    auto *test = new std::set<int>();
    auto *const trees = new ::myLibrary::SimpleSearchTree<int>();
    const int size = 2000;

    for (int i = 0; i<size; i++) {
        int r = rand() % size;
        if (test->count(r) < 1)
            test->insert(r);
    }
    auto begin = std::chrono::steady_clock::now();
    trees->insertAll(test->begin(), test->end());
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    ASSERT_EQ(true, trees->isValideTree(trees->root));
    for (std::__1::__tree_const_iterator<int, std::__1::__tree_node<int, void *> *, long>::value_type i: *test) {
        ASSERT_EQ(true, trees->contains(i));
        //std::cout << i << std::endl;
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
