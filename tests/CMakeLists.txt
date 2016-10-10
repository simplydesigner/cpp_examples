cmake_minimum_required(VERSION 3.5.2)
project(cpp_examples_test CXX)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
