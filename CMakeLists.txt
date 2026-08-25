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
    src/market_data/simulated_feed.cpp
    src/order_book/order_book.cpp
    src/order_book/price_level.cpp
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

add_executable(simulated_feed_test
    src/market_data/simulated_feed.cpp
    tests/market_data/simulated_feed_test.cpp
)

target_include_directories(simulated_feed_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

add_executable(order_book_test
    src/order_book/order_book.cpp
    src/order_book/price_level.cpp
    tests/order_book_test/order_book_test.cpp
    tests/order_book_test/price_level_test.cpp
)

target_include_directories(order_book_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

target_link_libraries(order_book_test
    PRIVATE
        GTest::gtest_main
)

target_link_libraries(simulated_feed_test
    PRIVATE
        GTest::gtest_main
)

gtest_discover_tests(simulated_feed_test)

gtest_discover_tests(order_book_test)

include(GoogleTest)