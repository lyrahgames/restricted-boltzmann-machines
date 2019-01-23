cmake_minimum_required(VERSION 3.10)
project(restricted-boltzmann-machines VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

add_subdirectory(movielens)
add_subdirectory(tests)

add_executable(main
  main.cc
)

target_link_libraries(main
  PRIVATE
    movielens
)