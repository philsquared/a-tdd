cmake_minimum_required(VERSION 3.10)
project(TDDAirClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(third-party/boost_srcs)
include_directories(third-party)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TDDAirClient
        request.h
        request.cpp
        model.h
        model.cpp
        tests.cpp)

target_link_libraries(
        TDDAirClient
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(TDDAirClient)