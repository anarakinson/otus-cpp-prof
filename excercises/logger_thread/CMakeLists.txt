cmake_minimum_required(VERSION 3.5) 

project(logger)


add_executable(logger logger.cpp)

set_target_properties(
    logger PROPERTIES 
    CXX_STANDARD 20 
    CXX_STANDARD_REQUIRED ON 
)