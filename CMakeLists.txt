cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)

project(cos_benchmarks
    LANGUAGES C
    VERSION 0.1
    DESCRIPTION "cos implementation benchmarks"
)

add_executable(benchmarks benchmarks.c)
target_link_libraries(benchmarks PRIVATE m)
