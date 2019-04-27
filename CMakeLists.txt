# cmakeのドキュメントはググればでる

# Basic {{{
cmake_minimum_required(VERSION 3.12)
project(cmake_example LANGUAGES CXX)
enable_testing()

# 本来はコンパイルオプションで指定するが，
# このプロジェクトにはDebugしか必要ないため
# おそらく，それぞれのビルドタイプにたいして，
# デフォルトの引数がいくつかある
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --coverage -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
# }}}

file(GLOB SOURCES src/**/*.cpp src/*.cpp)

# ヘッダーとかがおいてある include/ 的なファイルの探し先を指定する
# include_directories(src) # ?

add_subdirectory(test)

