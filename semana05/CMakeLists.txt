cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project("teste")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(OpenCV)

add_executable(main
    img_processing.cpp
    main.cpp)

message(${OpenCV_LIBS})
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(main ${OpenCV_LIBS})

