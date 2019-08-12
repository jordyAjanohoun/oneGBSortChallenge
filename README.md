# oneGBSortChallenge
Sort 1GB of data using MPI. Can you beat the time record? Amazon gift card for the winner! #PRACE #SoHPC2019 #HPC #BigData #Challenge #oneGBSortChallenge

## How to take part
1. clone the repository
2. fill the sort function in ***include/sort/sort.hpp*** with your sorting algorithm
3. run the ***run_correctness_test.sh*** script to build everything and run the correctness test
4. once the correctness passed, run the ***run_benchmark.sh*** script to benchmark your sort
5. when confident with your benchmark results, submit a ***pull request*** with your function

Your solution will be run with **1, 2 and 4 processes, on the same hardware** for everybody! 
The CPUs used for that are [Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz](https://ark.intel.com/content/www/us/en/ark/products/95451/intel-core-i7-7500u-processor-4m-cache-up-to-3-50-ghz.html "Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz"). 2 physical cores, 4 logical cores in total.  
The best time among the three will be kept and will appear within 24 hours here, in **Records** section below, accompanied by your username.

There is no limitation on the number of attempts.

## Rules about the sort
- MPI routines are allowed
- OpenMP is not allowed
- The entire array to sort is distributed across several processes:
  * each process has the same amount of data
  * after sorting, the lower rank process should have the lower part of the sorted array and so on
- We assume that one process can't hold the entire distributed array, this is why it is distributed
  * *Thus, your sort should never gather the entire array on one process*
- That's all. Be creative.

## Records
| Username | Time | Reward |
| :---: | :---: | :---: |
| [@jordyAjanohoun](https://github.com/jordyAjanohoun "github.com/jordyAjanohoun") | **1741 ms** | none |

## Reward
The rewards are **Amazon gift cards**. The first to reach one of these targets will earn the corresponding reward. **Each reward can be won only once**. They can be accumulated, e.g., if the first person to beat the record makes **less than 1000 ms**, she or he will earn **USD 100** and **there will be no more reward to win**.

| Time | Amount |
| :---: | :---: |
| Between **1740** and **1700 ms** | **USD 10** |
| Between **1699** and **1000 ms** | **USD 30** |
| Less than **1000 ms** | **USD 60** |


My solution will be published through the [PRACE Summer of HPC 2019](https://summerofhpc.prace-ri.eu/prace-summer-of-hpc-2019-opens-applications/ "PRACE Summer of HPC 2019"), a program in which I take part. More information about **PRACE** [**here**](http://www.prace-ri.eu/ "PRACE"). 
