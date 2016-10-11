cmake_minimum_required(VERSION 3.5.2)
project(cpp_examples_test CXX)

file(GLOB SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} cpp_examples)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} "-r" "compact" "--use-colour" "yes")
