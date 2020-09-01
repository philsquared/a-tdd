cmake_minimum_required(VERSION 3.12)
project(BankAccount)

set(CMAKE_CXX_STANDARD 17)

add_executable(BankAccount main.cpp BankAccount.cpp BankAccount.h Logger.cpp Logger.h Tests.cpp)