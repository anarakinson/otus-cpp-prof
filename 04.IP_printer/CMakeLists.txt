cmake_minimum_required(VERSION 3.5)

### set version
set(PATCH_VERSION "1" CACHE INTERNAL "IP Filter")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(print_ip VERSION ${PROJECT_VERSION})


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


### Deb pkg release ###
install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)
