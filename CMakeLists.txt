cmake_minimum_required (VERSION 3.6)

project (CharlaTDD)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wextra -Werror")

subdirs(src tdd)
