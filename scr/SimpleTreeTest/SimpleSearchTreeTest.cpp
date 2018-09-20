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

    delete tree;
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

    trees->insertAllbad(test->begin(), test->end());
    ASSERT_EQ(true, trees->contains(1));
    ASSERT_EQ(true, trees->contains(2));
    ASSERT_EQ(true, trees->contains(3));
    ASSERT_EQ(true, trees->contains(4));
    ASSERT_EQ(true, trees->contains(5));

    delete test;
    delete trees;
}

TEST(SimpleSearchTree, SimpleRemove) {
    auto *const trees = new ::myLibrary::SimpleSearchTree<int>();
    trees->insert(1);
    trees->insert(2);
    trees->insert(3);
    trees->insert(4);
    ASSERT_EQ(trees->remove(4), true);
    ASSERT_EQ(trees->remove(2), true);
    delete trees;
}

TEST(SimpleSearchTree, SpeedOfManyInsert) {
    auto *test = new std::set<int>();
    auto * trees = new ::myLibrary::SimpleSearchTree<int>();
    int size = 15000;

    for (int i = 0; i<size; i++) {
        int r = rand() % size;
        if (test->count(r) < 1)
            test->insert(r);
    }
    auto begin = std::chrono::steady_clock::now();
    trees->insertAll1(test->begin(), test->end());
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time1: " << elapsed_ms.count() << " ms\n";
    ASSERT_EQ(true, trees->isValideTree(trees->root));
    for (auto i = test->begin(); i != test->end(); i++) {
        ASSERT_EQ(true, trees->contains(*i));
        //std::cout << i << std::endl;
    }
    delete test;
    delete trees;

}

TEST(SimpleSearchTree, TestConstructorUsedIterator) {
    auto *test = new std::vector<int>();

    test->reserve(4);

    test->push_back(1);
    test->push_back(2);
    test->push_back(3);
    test->push_back(4);


    auto trees = new ::myLibrary::SimpleSearchTree<int>(begin(*test), end(*test)-1);

    ASSERT_EQ(true, trees->isValideTree(trees->root));


    ASSERT_EQ(true, trees->contains(1));
    ASSERT_EQ(true, trees->contains(2));
    ASSERT_EQ(true, trees->contains(3));
    ASSERT_EQ(true, trees->contains(4));


    delete test;
    delete trees;
}

TEST(SimpleSearchTree, TestInsertAll) {

    auto *test = new std::vector<int>();

    test->reserve(6);

    test->push_back(13);
    test->push_back(16);
    test->push_back(17);
    test->push_back(18);
    test->push_back(45);
    test->push_back(46);



    auto trees = new ::myLibrary::SimpleSearchTree<int>();

    trees->insert(10);
    trees->insert(5);
    trees->insert(20);
    trees->insert(15);
    trees->insert(30);
    trees->insert(25);
    trees->insert(40);

    trees->insertAll(test->begin(), test->end()-1);


    ASSERT_EQ(true, trees->isValideTree(trees->root));



    ASSERT_EQ(true, trees->contains(10));
    ASSERT_EQ(true, trees->contains(5));
    ASSERT_EQ(true, trees->contains(20));
    ASSERT_EQ(true, trees->contains(15));
    ASSERT_EQ(true, trees->contains(15));
    ASSERT_EQ(true, trees->contains(30));
    ASSERT_EQ(true, trees->contains(25));
    ASSERT_EQ(true, trees->contains(40));



    delete trees;
}
TEST(SimpleSearchTree, TestPair) {
    auto *test = new std::vector<int>();

    test->reserve(7);



    auto trees = new ::myLibrary::SimpleSearchTree<int>();


    ASSERT_EQ(true, trees->isValideTree(trees->root));


    ASSERT_EQ(true, trees->contains(10));
    ASSERT_EQ(true, trees->contains(5));
    ASSERT_EQ(true, trees->contains(20));
    ASSERT_EQ(true, trees->contains(15));
    ASSERT_EQ(true, trees->contains(25));
    ASSERT_EQ(true, trees->contains(40));




    delete test;
    delete trees;
}




TEST(SimpleSearchTree, TestInsertAll1) {
    auto *test = new std::vector<int>();
    auto trees = new ::myLibrary::SimpleSearchTree<int>();
    for (int i = 0; i < 10000; ++i) {
        test->push_back(i);
    }
    auto begin1 = std::chrono::steady_clock::now();
    trees->insertAll(begin(*test), end(*test)-1);
    auto end1 = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
    std::cout << "The time1: " << elapsed_ms.count() << " ms\n";




    ASSERT_EQ(true, trees->isValideTree(trees->root));


    ASSERT_EQ(true, trees->contains(1));
    ASSERT_EQ(true, trees->contains(2));
    ASSERT_EQ(true, trees->contains(3));
    ASSERT_EQ(true, trees->contains(4));


    delete test;
    delete trees;
}


TEST(SimpleSearchTree, TestAddAll) {
    auto *test = new std::vector<int>();

    test->reserve(3);

    test->push_back(3);
    test->push_back(7);
    test->push_back(15);


    auto trees = new ::myLibrary::SimpleSearchTree<int>();
    trees->insert(10);
    trees->insert(5);
    trees->insertAll1(begin(*test), end(*test));
    ASSERT_EQ(true, trees->isValideTree(trees->root));

    ASSERT_EQ(true, trees->contains(3));
    ASSERT_EQ(true, trees->contains(7));
    ASSERT_EQ(true, trees->contains(15));
    ASSERT_EQ(true, trees->contains(10));
    ASSERT_EQ(true, trees->contains(5));


    delete test;
    delete trees;
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
