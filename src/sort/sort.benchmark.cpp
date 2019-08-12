#include "sort.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <chrono>
#include <mpi.h>
#include <random>
#include <vector>

// the entire distributed array to sort is called global array
const unsigned long GLOBAL_ARRAY_SIZE = 1 << 30;
const std::vector<unsigned> SEEDS = {1, 2, 13, 38993, 83030, 90, 25, 28, 10, 73};

void your_sort_benchmark(benchmark::State &state) {

        int my_rank = -1;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        int comm_size = -1;
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        // the GLOBAL ARRAY SIZE should be a multiple of the number of procs
        // in order to have the same amount of data on each proc
        ASSERT_EQ(GLOBAL_ARRAY_SIZE % comm_size, 0) << "GLOBAL_ARRAY_SIZE is not a multiple of comm_size";

        const unsigned long local_array_size = GLOBAL_ARRAY_SIZE / comm_size;

        // the part of the global array held by this process (called local array)
        std::vector<int8_t> local_test_vec(local_array_size);

        double iteration_time{};

        // see google benchmark doc for more information about benchmarking with the framework
        while (state.KeepRunning()) {

                for (const auto &seed : SEEDS) {

                        // benchmark with multiple arrays by using different seeds to generate the global array

                        // get the global array portion of this process and sort the global array
                        std::mt19937 g(seed);
                        g.discard(local_array_size * my_rank);
                        std::generate(local_test_vec.begin(), local_test_vec.end(), g);

                        MPI_Barrier(MPI_COMM_WORLD);

                        // Do the work and time it on each proc
                        auto start = std::chrono::high_resolution_clock::now();
                        your_sort(local_test_vec.begin(), local_test_vec.end(), MPI_INT8_T, MPI_COMM_WORLD);
                        auto end = std::chrono::high_resolution_clock::now();
                        // Now get the max time across all procs:
                        // for better or for worse, the slowest processor is the one that is
                        // holding back the others in the benchmark.
                        auto const duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
                        auto elapsed_seconds = duration.count();
                        double max_elapsed_second{};
                        MPI_Allreduce(&elapsed_seconds, &max_elapsed_second, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

                        iteration_time += max_elapsed_second;
                }

                iteration_time /= SEEDS.size();
                state.SetIterationTime(iteration_time);
        }
}

BENCHMARK(your_sort_benchmark)->Arg(GLOBAL_ARRAY_SIZE)->UseManualTime()->Unit(benchmark::kMillisecond);

void std_sort_benchmark(benchmark::State &state) {

        /*
                only one process will run this
                it's just to have a reference to compare your_sort and the std sort sorting the whole global array on one proc
        */

        // the entire global array to sort
        std::vector<int8_t> global_test_vec(GLOBAL_ARRAY_SIZE);

        double iteration_time{};

        while (state.KeepRunning()) {

                for (const auto &seed : SEEDS) {

                        // benchmark with multiple arrays by using different seeds to generate the global array

                        std::mt19937 g(seed);
                        std::generate(global_test_vec.begin(), global_test_vec.end(), g);

                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(global_test_vec.begin(), global_test_vec.end());
                        auto end = std::chrono::high_resolution_clock::now();

                        auto const duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

                        iteration_time += duration.count();
                }

                iteration_time /= SEEDS.size();
                state.SetIterationTime(iteration_time);
        }
}

BENCHMARK(std_sort_benchmark)->Arg(GLOBAL_ARRAY_SIZE)->UseManualTime()->Unit(benchmark::kMillisecond);