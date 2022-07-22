cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(FetchContent
  LANGUAGES CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "Just some of my frequently used FetchContent scripts"
)

include(FetchContent)

#
#  Including Google Benchmark
#
set(BENCHMARK_ENABLE_GTEST_TESTS off)
FetchContent_Declare(
  GoogleBenchmarkContent
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.6.2
)
FetchContent_GetProperties(GoogleBenchmarkContent)
if(NOT googlebenchmarkcontent_POPULATED)
  FetchContent_Populate(GoogleBenchmarkContent)
  add_subdirectory(
    ${googlebenchmarkcontent_SOURCE_DIR}
    ${googlebenchmarkcontent_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endif()

add_executable(GoogleBenchmark Source/GoogleBenchmark.cc)
target_link_libraries(GoogleBenchmark PRIVATE benchmark::benchmark)

include(FetchContent)

#
#  Including GTest
#
FetchContent_Declare(
  GoogleTestContent
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.12.0
)
FetchContent_GetProperties(GoogleTestContent)
if(NOT googletestcontent_POPULATED)
  FetchContent_Populate(GoogleTestContent)
  add_subdirectory(
    ${googletestcontent_SOURCE_DIR}
    ${googletestcontent_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endif()

add_executable(GoogleTest Source/GoogleTest.cc)
target_link_libraries(GoogleTest PRIVATE GTest::gtest_main)
