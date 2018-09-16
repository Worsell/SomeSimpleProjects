project(Tree)
set(tree_source Node.h SimpleSearchTree.h Node.cpp SimpleSearchTree.cpp)
add_library(tree STATIC ${tree_source})
