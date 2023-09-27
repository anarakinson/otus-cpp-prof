cmake_minimum_required(VERSION 3.5)


project(ip_filter)


# sources
add_executable(ip_filter src/ip_filter.cpp)


# set target properties
set_target_properties(
    ip_filter
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)


# set include directories
target_include_directories(
    ip_filter
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
)


# set compile options
if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


# enable_testing()

# add_test(test test)

