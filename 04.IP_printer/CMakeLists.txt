cmake_minimum_required(VERSION 3.5)


project(04.ip_printer)


add_executable(ip_printer
    ip_printer.cpp
)


set_target_properties(
    ip_printer
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# set compile options
if (MSVC)
    target_compile_options(ip_printer PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_printer PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()