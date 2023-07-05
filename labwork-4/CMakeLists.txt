cmake_minimum_required(VERSION 3.23)
project(lab4)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp ParserSystem.cpp ParserSystem.h ArchiveSystem.cpp ArchiveSystem.h Header.cpp Header.h HammingSystem.cpp HammingSystem.h)
