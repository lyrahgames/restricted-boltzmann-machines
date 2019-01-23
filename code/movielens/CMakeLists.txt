cmake_minimum_required(VERSION 3.10)
project(movielens VERSION 0.1.0 LANGUAGES CXX)

enable_testing()

add_library(movielens
  movie_dataset.cc
  rating_dataset.cc
)

target_include_directories(movielens PUBLIC ..)

target_compile_features(movielens
  PUBLIC
    cxx_std_17
)