cmake_minimum_required(VERSION 3.13)
project(My_Solution_2)

set(CMAKE_CXX_STANDARD 11)
set("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -fsanitize-memory-track-origins LSAN_OPTIONS=report_objects=1 -g -OX")
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(My_Solution_2 main.cpp File.hpp File.cpp Counter.cpp Counter.hpp Entry.hpp Entry.cpp)