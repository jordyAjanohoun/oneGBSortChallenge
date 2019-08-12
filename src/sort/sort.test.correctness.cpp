#include "sort.hpp"
#include <algorithm>
#include <catch2/catch.hpp>
#include <mpi.h>
#include <random>
#include <vector>

TEST_CASE("your_sort correctness test", "[correctness]") {

        int comm_size = -1;
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        int my_rank = -1;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // test with several array sizes - refer to Catch2 testing framework doc for more explanation about GENERATE
        unsigned int local_array_size = GENERATE(0, 1, 100, 1000, 10000, 100000);

        // the entire distributed array to sort (called global array)
        std::vector<int8_t> global_test_vec(local_array_size * comm_size);

        // the part of the global array held by this process (called local array)
        std::vector<int8_t> local_test_vec(local_array_size);

        unsigned seed = GENERATE(0, 1, 5, 13, 575, 27877, 8927);
        std::mt19937 g(seed);

        std::generate(global_test_vec.begin(), global_test_vec.end(), g);

        // each process gets its part of the global array according to its rank
        std::copy(global_test_vec.begin() + local_array_size * my_rank, global_test_vec.begin() + local_array_size * (my_rank + 1), local_test_vec.begin());

        MPI_Barrier(MPI_COMM_WORLD);

        your_sort(local_test_vec.begin(), local_test_vec.end(), MPI_INT8_T, MPI_COMM_WORLD);

        // sort the global array and check if your sort has well-sorted the distributed array
        std::sort(global_test_vec.begin(), global_test_vec.end());

        bool is_locally_sorted = std::equal(global_test_vec.begin() + local_array_size * my_rank, global_test_vec.begin() + local_array_size * (my_rank + 1), local_test_vec.begin());

        REQUIRE(is_locally_sorted == true);
}