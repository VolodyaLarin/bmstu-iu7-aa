cmake_minimum_required(VERSION 3.19)
project(app)

set(CMAKE_CXX_STANDARD 17)

add_executable(app main.cpp src/compare.cpp src/conveyor.cpp src/matrix.cpp src/read.cpp)

target_link_libraries(${PROJECT_NAME} pthread)