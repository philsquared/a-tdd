cmake_minimum_required(VERSION 3.20)
project(snakes_and_ladders)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(snakes_and_ladders main.cpp)

target_link_libraries(
        snakes_and_ladders
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(snakes_and_ladders)
