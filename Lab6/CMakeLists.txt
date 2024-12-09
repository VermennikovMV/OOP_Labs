cmake_minimum_required(VERSION 3.10)
project(lab6)
set(CUR_PR "lab6")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

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
add_library(${CUR_PR}_lib ${SOURCES})

add_executable(${CUR_PR}_exe main.cpp)
target_link_libraries(${CUR_PR}_exe PRIVATE ${CUR_PR}_lib)

add_executable(${CUR_PR}_tests test/tests01.cpp)
target_link_libraries(${CUR_PR}_tests ${CUR_PR}_lib gtest_main)

add_test(NAME ${CUR_PR}tests COMMAND ${CUR_PR}_tests)
