file(GLOB TESTS **/*.cpp *.cpp)
# set(TESTFILES primes.cpp )

include(CodeCoverage)
append_coverage_compiler_flags()

set(TEST_MAIN unit_tests)
set(TEST_RUNNER_PARMS "--gtest_color=yes")

foreach(test ${TESTS})
  get_filename_component(we ${test} NAME_WE)
  add_executable(${we} ${test})
  target_link_libraries(${we} PRIVATE GTest::GTest GTest::Main)
  add_test(${we} ${we})
  setup_target_for_coverage_gcovr_html(
    NAME ${we}.coverage
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
    DEPENDENCIES ${we}
    )
endforeach()

