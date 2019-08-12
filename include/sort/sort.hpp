#include <algorithm>
#include <mpi.h>

template <class InputIt> void your_sort(const InputIt &begin, const InputIt &end, MPI_Datatype datatype, MPI_Comm comm) {

        /*
            #oneGBSortChallenge

            Replace std::sort by your sorting algorithm
            MPI routines are allowed
            OpenMP is not allowed
            The entire list to sort is distributed across several processes:
                -- each process has the same amount of data
                -- the lower rank process should have the lower part of the sorted list and so on
                -- The range used for each process is [begin,end),
                    which contains all the elements between begin and end,
                    including the element pointed by begin but not the element pointed by end

            We assume that one process can't hold the entire distributed array, this is why it is distributed
            	Thus, your sort should never gather the entire array on one process

            Can you beat my time record? Amazon gift card for the winner!
        */

        std::sort(begin, end);
}
