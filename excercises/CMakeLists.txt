cmake_minimum_required(VERSION 3.15)


project(exercises CXX)


file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")


foreach(src_file ${SRC_FILES})
    get_filename_component(target ${src_file} NAME_WLE)
    add_executable(${target} ${src_file})
    list(APPEND TARGETS ${target})
    message("target added: ${target}")
endforeach(src_file ${SRC_FILES})


set_target_properties(
    ${TARGETS}
    PROPERTIES CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)


if(
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
)
    foreach(TARGET ${TARGETS})
        target_compile_options(
            ${TARGET}
            PRIVATE -g -Wall -Wextra -Werror -pedantic
        )
    endforeach()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    foreach(TARGET ${TARGETS})
        target_compile_options(
            ${TARGET}
            PRIVATE /W4 /WX
        )
    endforeach()
endif()
