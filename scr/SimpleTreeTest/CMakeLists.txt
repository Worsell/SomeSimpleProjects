project(Tests)
cmake_minimum_required(VERSION 3.12)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


set(BinaryTest_source SimpleSearchTreeTest.cpp)
add_executable(BinaryTest ${BinaryTest_source})
target_link_libraries(BinaryTest gtest gtest_main BinaryTree)

add_test(NAME Test1 COMMAND BinaryTest)


set(BTreeTests_Source BTreeTest.cpp)
add_executable(BTreeTest ${BTreeTests_Source})
target_link_libraries(BTreeTest gtest gtest_main BTree)

add_test(NAME Test2 COMMAND BTreeTest)
