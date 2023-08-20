set(CMAKE_COLOR_DIAGNOSTICS ON)
add_library(asm SHARED Encoder.cpp AsmParser.cpp)
target_include_directories(asm PUBLIC ${PROJECT_SOURCE_DIR}/include)