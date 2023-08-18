cmake_minimum_required(VERSION 3.22)
project(asmkheiv CXX)

set(CMAKE_CXX_FLAGS "-Wall -march=native -fPIC ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

include_directories(include)
add_subdirectory(lib)

add_executable(asmkheiv main.cpp)

target_link_libraries(asmkheiv encoder)

# enable unit tests

add_subdirectory(unittests)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_test(NAME unit COMMAND ctest --test-dir ./build/unittests/)