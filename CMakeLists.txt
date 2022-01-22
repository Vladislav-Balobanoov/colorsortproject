# CMakeList.txt: проект CMake для ASTest; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.16)

project(colorsorting VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(GTest CONFIG)
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable (
    ${PROJECT_NAME}
    "main.cpp" 
    "additonalfunc.hpp" 
    "subject.hpp"
    "rthread.hpp"
)