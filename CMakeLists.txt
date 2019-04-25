cmake_minimum_required(VERSION 3.0)
project(cmake_example CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_executable(a a.cpp)
target_link_libraries(a
    PUBLIC
    GTest::GTest
    GTest::Main
    )
