cmake_minimum_required(VERSION 3.23)
project(labwork_3_SunLYous)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)

add_executable(labwork_3_SunLYous main.cpp ParsingSystem.cpp ParsingSystem.h ScatteringSystem.cpp ScatteringSystem.h ImageSystem.cpp ImageSystem.h)
