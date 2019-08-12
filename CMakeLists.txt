cmake_minimum_required(VERSION 3.12)

project(oneGBSortChallenge VERSION 1.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MPI REQUIRED)

# build Catch2 test environment (target: Catch2::Catch2)
add_subdirectory(external/Catch2)

# build catch2 and google benchmark custom main (targets: catch2_runner and google_benchmark_runner)
add_subdirectory(tests)

# build google test (target: gtest)
add_subdirectory(external/google/benchmark/googletest)

# build google benchmark (target: benchmark)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES OFF CACHE BOOL "Disabling download dependencies" FORCE)
add_subdirectory(external/google/benchmark)


# build correctness test (target: sort.test.correctness)
add_executable(sort.test.correctness src/sort/sort.test.correctness.cpp include/sort/sort.hpp)
target_include_directories(sort.test.correctness PRIVATE include/sort)
target_link_libraries(sort.test.correctness PRIVATE catch2_runner)


# build benchmarking (target: sort.benchmark)
add_executable(sort.benchmark src/sort/sort.benchmark.cpp include/sort/sort.hpp)
target_include_directories(sort.benchmark PRIVATE include/sort)
target_link_libraries(sort.benchmark PRIVATE google_benchmark_runner)

enable_testing()

# add correctness tests to test
add_test(NAME correctness_test_1_proc
	COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 1 ${MPIEXEC_PREFLAGS} $<TARGET_FILE:sort.test.correctness> ${MPIEXEC_POSTFLAGS})

add_test(NAME correctness_test_2_proc
	COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 2 ${MPIEXEC_PREFLAGS} $<TARGET_FILE:sort.test.correctness> ${MPIEXEC_POSTFLAGS})

add_test(NAME correctness_test_4_proc
	COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${MPIEXEC_PREFLAGS} $<TARGET_FILE:sort.test.correctness> ${MPIEXEC_POSTFLAGS})