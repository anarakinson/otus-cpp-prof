cmake_minimum_required(VERSION 3.5) 

project(sqlite)


find_package(unofficial-sqlite3 CONFIG REQUIRED)


add_executable(main main.cpp) 


set_target_properties(
    main PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

include_directories(
    "include"
)    

target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

