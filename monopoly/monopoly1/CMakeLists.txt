cmake_minimum_required(VERSION 3.10)
project(monopoly1)

set(CMAKE_CXX_STANDARD 14)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(monopoly1 main.cpp)

target_link_libraries(
        monopoly1
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(monopoly1)