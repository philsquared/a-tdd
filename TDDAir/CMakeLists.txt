cmake_minimum_required(VERSION 3.20)
project(TDDAir)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        TDDAir
        tests.cpp
        Flight.cpp
        Flight.h
        MemberTests.cpp
)

target_link_libraries(
        TDDAir
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(TDDAir)
