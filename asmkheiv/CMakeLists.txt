cmake_minimum_required(VERSION 3.22)
project(asmkheiv CXX)
set (CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)

set(CMAKE_CXX_FLAGS "-Wall -march=native -fPIC  ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_COLOR_DIAGNOSTICS ON)

# TODO switch on off by CMAKE option
message(STATUS "build on ${CMAKE_SYSTEM_NAME}, ${CMAKE_SYSTEM_PROCESSOR}")

# You can disable SANITIZE by cmake -DSANITIZE=OFF ..
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    option(SANITIZE "Enable sanitize options" ON)
else()
    option(SANITIZE "Enable sanitize options" OFF)
endif()

if (SANITIZE)
  set(CMAKE_CXX_FLAGS "-g -fsanitize=address -fsanitize=leak -fsanitize=undefined ${CMAKE_CXX_FLAGS}")
endif()

add_custom_target(build ALL)



include_directories(include)
add_subdirectory(lib)

add_executable(asmkheiv main.cpp)

target_link_libraries(asmkheiv asm)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable unit tests
add_subdirectory(unittests)

add_custom_target(unittests
  COMMAND ctest --test-dir ./unittests/ --output-on-failure 
  DEPENDS asmkheiv ${ALL_TESTS}
)
set(CMAKE_COLOR_DIAGNOSTICS ON)

# TODO: put some tests on build di
add_custom_target(run
  COMMAND ./asmkheiv ../tests/addi.s
  DEPENDS asmkheiv
  )

add_custom_target(format find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})