#include <BTree.h>

using namespace tree;

int main(int argc) {
    BTree<int> bTree = BTree<int>(2);
    bTree.insert(12);
    bTree.insert(13);
    bTree.insert(234);
    bTree.insert(232);
    bTree.insert(546);
    bTree.insert(238);
    bTree.insert(231);
    bTree.insert(435);
    bTree.insert(54);
    bTree.search(12);
    bTree.search(13);
    bTree.search(234);
    bTree.search(232);
    bTree.search(546);
    bTree.search(238);
    bTree.search(231);
    bTree.search(435);
    bTree.remove(54);
    bTree.remove(12);
    bTree.remove(13);
    bTree.remove(234);
    bTree.remove(232);
    bTree.remove(546);
    bTree.remove(238);
    bTree.remove(231);
    bTree.remove(435);
    bTree.remove(54);

    return 0;
}
