cmake_minimum_required(VERSION 3.14)
project(icpc-train-22-23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DONPC -fsanitize=address -fsanitize=undefined")

add_executable(A1 contest-01/A1.cpp)