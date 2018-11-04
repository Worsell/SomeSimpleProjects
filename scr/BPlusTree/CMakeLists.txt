project(TreeBPlus)
set(Bplus_tree_source BTree.h Node.h BTree.cpp Node.cpp SmartBTree.cpp SmartBTree.h)
add_library(BTree STATIC ${Bplus_tree_source})
