cmake_minimum_required(VERSION 3.12)
project(BankAccount)

set(CMAKE_CXX_STANDARD 14)


include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(BankAccount BankAccount.cpp BankAccount.h Logger.cpp Logger.h Tests.cpp)

target_link_libraries(
        BankAccount
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(BankAccount)