project(TreeBinary)
set(binary_tree_source Node.h SimpleSearchTree.h Node.cpp SimpleSearchTree.cpp)
add_library(BinaryTree STATIC ${binary_tree_source})
