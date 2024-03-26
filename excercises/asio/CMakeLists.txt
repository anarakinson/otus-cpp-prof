cmake_minimum_required(VERSION 3.5)

project(asio)


###
find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)
include_directories(${Boost_INCLUDE_DIR})

###

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})

set_target_properties(
    ${TARGETS}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

include_directories(
    "./include"
)

link_libraries(
    ${TARGETS}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

