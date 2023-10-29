cmake_minimum_required(VERSION 3.5)

### set version
set(PATCH_VERSION "1" CACHE INTERNAL "Matrix")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(06.matrix VERSION ${PROJECT_VERSION})


add_executable(
    matrix
    main.cpp
)

target_include_directories(
    matrix
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(
    matrix
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# set compile options
if (MSVC)
    target_compile_options(matrix PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


### Deb pkg release ###
install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)
