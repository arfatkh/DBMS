cmake_minimum_required(VERSION 3.23)
project(DBMS)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(DBMS
        AVLTree.h
        BTree.h
        Filehandling.h
        Others.h
        RBTree.h
        Source.cpp)
