cmake_minimum_required(VERSION 3.5)


project(03.allocator)


add_executable(allocator
    allocator.cpp
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
