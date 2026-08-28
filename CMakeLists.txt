cmake_minimum_required(VERSION 3.20)

project(lynx_hft
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------
# Compiler warnings
# -------------------------

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
)

# -------------------------
# Sanitizers / Static Analysis
# -------------------------

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)

if(ENABLE_ASAN)
    message(STATUS "AddressSanitizer enabled")

    add_compile_options(
        -fsanitize=address
        -fno-omit-frame-pointer
    )

    add_link_options(
        -fsanitize=address
    )
endif()

if(ENABLE_UBSAN)
    message(STATUS "UndefinedBehaviorSanitizer enabled")

    add_compile_options(
        -fsanitize=undefined
        -fno-omit-frame-pointer
    )

    add_link_options(
        -fsanitize=undefined
    )
endif()

if(ENABLE_TSAN)
    message(STATUS "ThreadSanitizer enabled")

    add_compile_options(
        -fsanitize=thread
        -fno-omit-frame-pointer
    )

    add_link_options(
        -fsanitize=thread
    )
endif()

# -------------------------
# clang-tidy
# -------------------------

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY clang-tidy REQUIRED)

    # clang++ may discover a different GCC installation than the
    # compiler selected by CMake. Ask the selected compiler where
    # its GCC-specific include directory is located.
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=include
        OUTPUT_VARIABLE GCC_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE GCC_INCLUDE_RESULT
    )

    if(NOT GCC_INCLUDE_RESULT EQUAL 0)
        message(FATAL_ERROR
            "Failed to determine GCC include directory from "
            "${CMAKE_CXX_COMPILER}"
        )
    endif()

    get_filename_component(
        GCC_INSTALL_DIR
        "${GCC_INCLUDE_DIR}/.."
        ABSOLUTE
    )

    message(STATUS "clang-tidy enabled: ${CLANG_TIDY}")
    message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
    message(STATUS "GCC install dir: ${GCC_INSTALL_DIR}")

    set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY}"
        "--extra-arg-before=--driver-mode=g++"
        "--extra-arg-before=--gcc-install-dir=${GCC_INSTALL_DIR}"
    )
endif()

# -------------------------
# Main executable
# -------------------------

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

include(GoogleTest)

add_executable(simulated_feed_test
    src/market_data/simulated_feed.cpp
    tests/market_data/simulated_feed_test.cpp
)

target_include_directories(simulated_feed_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

target_link_libraries(simulated_feed_test
    PRIVATE
        GTest::gtest_main
)

add_executable(order_book_test
    src/order_book/order_book.cpp
    src/order_book/price_level.cpp
    src/market_data/simulated_feed.cpp
    tests/order_book_test/order_book_test.cpp
    tests/order_book_test/price_level_test.cpp
    tests/market_data/order_book_feed_test.cpp
)

target_include_directories(order_book_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/header
)

target_link_libraries(order_book_test
    PRIVATE
        GTest::gtest_main
)

gtest_discover_tests(simulated_feed_test)
gtest_discover_tests(order_book_test)