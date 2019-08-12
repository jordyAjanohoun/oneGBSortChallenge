# build catch2 custom main
add_library(catch2_runner catch2_runner.main.cpp)
target_link_libraries(catch2_runner PUBLIC Catch2::Catch2 MPI::MPI_CXX)

# build google benchmark custom main
add_library(google_benchmark_runner google_benchmark_runner.main.cpp)
target_link_libraries(google_benchmark_runner PUBLIC gtest benchmark MPI::MPI_CXX)