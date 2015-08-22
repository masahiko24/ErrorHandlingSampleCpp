cmake_minimum_required(VERSION 3.3)
project(ErrorHandlingSampleCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FailableActor.cpp FailableActor.h ErrorContext.cpp ErrorContext.h Error.cpp Error.h)
add_executable(ErrorHandlingSampleCpp ${SOURCE_FILES})