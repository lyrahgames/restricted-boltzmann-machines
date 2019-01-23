find_package(doctest REQUIRED)

add_executable(main_test
  doctest_main.cc
  rbm.cc
)

target_compile_features(main_test
  PRIVATE
    cxx_std_17
)

target_link_libraries(main_test
  PRIVATE
    doctest::doctest
)

add_test(main_test main_test)