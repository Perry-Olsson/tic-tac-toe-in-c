cmake_minimum_required(VERSION 3.24.1)

project(TESTING)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ./src/main.c)
