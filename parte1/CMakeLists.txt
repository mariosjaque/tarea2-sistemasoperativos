cmake_minimum_required(VERSION 3.29)
project(Parte_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(simulapc main.cpp
        monitor.cpp
        circular_queue.cpp
        logger.cpp)
