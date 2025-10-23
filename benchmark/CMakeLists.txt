cmake_minimum_required(VERSION 3.16)
project(benchmark LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.5.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(ukf_benchmarks
    StateVectorBenchmark.cpp
    MeasurementVectorBenchmark.cpp
    CoreBenchmark.cpp
    SquareRootCoreBenchmark.cpp
    BenchmarkMain.cpp)

set_target_properties(ukf_benchmarks PROPERTIES OUTPUT_NAME benchmark)

add_dependencies(ukf_benchmarks eigen3)

target_compile_definitions(ukf_benchmarks PRIVATE EIGEN_NO_MALLOC UKF_DOUBLE_PRECISION)
target_include_directories(ukf_benchmarks PRIVATE ../include ${eigen_dir})
target_link_libraries(ukf_benchmarks PRIVATE benchmark::benchmark pthread)
