cmake_minimum_required(VERSION 3.10)
project(Lab5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создаём статическую библиотеку из cpp-файлов
add_library(${CMAKE_PROJECT_NAME}_lib
    src/my_struct.cpp
    src/custom_memory_resource.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC include)

# Основной исполняемый файл
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}_exe PUBLIC include)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(tests test/tests01.cpp)
target_include_directories(tests PUBLIC include)
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_test(NAME MyProjectTests COMMAND tests)
