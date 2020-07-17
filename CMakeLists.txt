cmake_minimum_required(VERSION 3.15)
project(poker)

set(CMAKE_CXX_STANDARD 14)

#set(INC_DIR /home/blah/armadillo-7.200.3/include)
#set(LINK_DIR /home/blah/armadillo-7.200.3/include)
#
#include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(armadillo)


add_library(lib src/lib/assemble.cpp)

add_executable(poker src/main.cpp)
target_link_libraries(poker lib)
