project(Tests)
cmake_minimum_required(VERSION 3.12)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


set(test1_source SimpleSearchTreeTest.cpp)
add_executable(maintest ${test1_source})
target_link_libraries(maintest gtest gtest_main tree)

add_test(NAME Test1 COMMAND maintest)
