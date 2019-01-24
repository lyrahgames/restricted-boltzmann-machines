cmake_minimum_required(VERSION 3.10)
project(movielens VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

find_package(Eigen3 REQUIRED)

add_library(movielens
  movie_dataset.cc
  rating_dataset.cc
  rbm.cc
)

target_include_directories(movielens PUBLIC ..)

target_compile_features(movielens
  PUBLIC
    cxx_std_17
)

target_link_libraries(movielens
  PUBLIC
    Eigen3::Eigen
)