cmake_minimum_required(VERSION 3.8)
project(cmake_example CXX)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_executable(a a.cpp)

target_compile_options(a PRIVATE -O2 -Wall -Wextra -Wpedantic -g)

target_link_libraries(a
  PRIVATE
  GTest::GTest
  GTest::Main
  )

add_test(
  NAME a
  COMMAND a --gtest_color=yes
  )

include(CodeCoverage)
# setup_target_for_coverage(${PROJECT_NAME}_coverage poptests coverage)
# setup_target_for_coverage_cobertura(${PROJECT_NAME}_cobertura poptests coverage --gtest_output=xml:coverage.junit.xml)

APPEND_COVERAGE_COMPILER_FLAGS()

SETUP_TARGET_FOR_COVERAGE_GCOVR_HTML(
    NAME ac                    # New target name
    EXECUTABLE a -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
    DEPENDENCIES a         # Dependencies to build first
)

