cmake_minimum_required (VERSION 2.6)

project(MetaData)

set(CMAKE_CXX_FLAGS "-std=c++17")

add_executable(
    MetaData 
    
    Headers.h

    Entry.cpp

    FileType.cpp

    FileSize.cpp
)