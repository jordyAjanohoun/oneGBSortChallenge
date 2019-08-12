#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <mpi.h>

/*
	Catch2 MPI main runner (the default Catch2 runner doesn't include MPI)
*/

// The main is rewritten to allow for MPI initializing

int main(int argc, char *argv[]) {
        // global setup
        MPI_Init(&argc, &argv);

        int result = Catch::Session().run(argc, argv);

        // global clean-up
        MPI_Finalize();

        return result;
}
