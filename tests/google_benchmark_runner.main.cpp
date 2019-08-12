#include <benchmark/benchmark.h>
#include <mpi.h>

/*
    google benchmark MPI main runner (the default google benchmark runner doesn't include MPI)
*/

// This reporter does nothing.
// We can use it to disable output from all except the rank 0 process
class NullReporter : public ::benchmark::BenchmarkReporter {
      public:
        NullReporter() {}
        virtual bool ReportContext(const Context &) { return true; }
        virtual void ReportRuns(const std::vector<Run> &) {}
        virtual void Finalize() {}
};

// The main is rewritten to allow for MPI initializing and for selecting a
// reporter according to the process rank
int main(int argc, char **argv) {

        MPI_Init(&argc, &argv);

        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        ::benchmark::Initialize(&argc, argv);

        if (my_rank == 0)
                // root process will use a reporter from the usual set provided by
                // ::benchmark
                ::benchmark::RunSpecifiedBenchmarks();
        else {
                // reporting from other processes is disabled by passing a custom reporter
                NullReporter null;
                ::benchmark::RunSpecifiedBenchmarks(&null);
        }

        MPI_Finalize();
        return 0;
}