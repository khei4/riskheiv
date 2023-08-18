enable_testing()

add_executable(
  tut
  tut.cpp
)
target_link_libraries(
  tut
  GTest::gtest_main
  encoder
)
target_include_directories(tut PUBLIC ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(tut)