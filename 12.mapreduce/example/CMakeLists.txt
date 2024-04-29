cmake_minimum_required(VERSION 3.5)

project(MapReduce VERSION 2.0.0.0 LANGUAGES C CXX)

add_executable(mapreduce MapReduce.cpp)

set_target_properties(
        mapreduce
        PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )


add_executable(homework ./homework/client.cpp ./homework/mapreduce.h)

set_target_properties(
        homework
        PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )