cmake_minimum_required(VERSION 3.5)

### set version
set(PATCH_VERSION "1" CACHE INTERNAL "Text Redactor")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(architecture VERSION ${PROJECT_VERSION})


add_executable(
    architecture
    main.cpp
)

target_include_directories(
    architecture
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(
    architecture
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# set compile options
if (MSVC)
    target_compile_options(architecture PRIVATE
        /W4
    )
else ()
    target_compile_options(architecture PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


### Deb pkg release ###
install(TARGETS architecture RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)
