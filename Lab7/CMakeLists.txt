cmake_minimum_required(VERSION 3.10)
project(lab7)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.cpp)

add_library(lab7_lib ${SOURCES})

add_executable(lab7_exe main.cpp)
target_link_libraries(lab7_exe PRIVATE lab7_lib)

add_executable(lab7_tests test/tests01.cpp)
target_link_libraries(lab7_tests lab7_lib gtest_main)

enable_testing()
add_test(NAME lab7tests COMMAND lab7_tests)
