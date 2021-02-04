cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project("vai")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(OpenCV)

add_executable(main main.cpp)

target_link_libraries(main ${OpenCV_LIBS})

