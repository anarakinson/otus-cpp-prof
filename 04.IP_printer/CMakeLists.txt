cmake_minimum_required(VERSION 3.5)


project(04.ip_printer)


add_executable(print_ip
    ip_printer.cpp
)


set_target_properties(
    print_ip
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# set compile options
if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()