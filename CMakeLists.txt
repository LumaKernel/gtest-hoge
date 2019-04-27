# Basic {{{
cmake_minimum_required(VERSION 3.12)
project(cmake_example LANGUAGES CXX)
enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic")

find_package(GTest REQUIRED)
# }}}

file(GLOB SOURCES src/**/*.cpp src/*.cpp)

include(Coveralls) # ファイルシステムによってケースセンシティブ
coveralls_turn_on_coverage()

# Create the coveralls target.
coveralls_setup(
  "${SOURCES}" # The source files.
  ON                 # If we should upload.
  )

# ヘッダーとかがおいてある include/ 的なファイルの探し先を指定する
# include_directories(src) # ?

add_subdirectory(test)

