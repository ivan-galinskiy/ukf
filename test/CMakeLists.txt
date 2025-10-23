cmake_minimum_required(VERSION 3.16)
project(unittest LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# Ensure MSVC compatibility if ever built there and avoid cache pollution.
set(gtest_force_shared_crt OFF CACHE BOOL "Use shared CRT" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unittest
    TestStateVector.cpp
    TestFixedMeasurementVector.cpp
    TestDynamicMeasurementVector.cpp
    TestCore.cpp
    TestSquareRootCore.cpp)

add_dependencies(unittest eigen3)

target_compile_definitions(unittest PRIVATE EIGEN_NO_MALLOC UKF_DOUBLE_PRECISION)
target_include_directories(unittest PRIVATE ../include ${eigen_dir})
target_link_libraries(unittest PRIVATE GTest::gtest GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(unittest)
