cmake_minimum_required(VERSION 3.20)

project(lynx_hft
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
)

add_executable(lynx
    src/main.cpp
    src/order_book/order_book.cpp
)

target_include_directories(lynx
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

# -------------------------
# Tests
# -------------------------

enable_testing()

find_package(GTest REQUIRED)

add_executable(order_book_test
    tests/order_book_test/order_book_test.cpp
    src/order_book/order_book.cpp
)

target_include_directories(order_book_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

target_link_libraries(order_book_test
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(order_book_test)