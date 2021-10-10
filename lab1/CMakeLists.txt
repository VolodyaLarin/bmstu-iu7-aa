project(lab1)

cmake_minimum_required(VERSION 3.20)


set (CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})


add_executable(main.cpp src/LevenshteinDistance.cpp src/DamerauLevenshteinDistance.cpp inc/DamerauLevenshteinDistance.h)
target_link_libraries( main.out ${Boost_LIBRARIES} )
