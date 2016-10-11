cmake_minimum_required(VERSION 3.5.2)
project(cpp_examples CXX)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
