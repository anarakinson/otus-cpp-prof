cmake_minimum_required(VERSION 3.5)


project(03.allocator)


add_executable(allocator
    allocator.cpp
)


target_include_directories(
    allocator
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)


set_target_properties(
    allocator
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# set compile options
if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
