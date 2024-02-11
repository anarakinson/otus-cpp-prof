cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bayan VERSION ${PROJECT_VERSION})


find_package(
    Boost COMPONENTS
    program_options REQUIRED
)

include_directories(${Boost_INCLUDE_DIR})


add_executable(
    bayan main.cpp
)


set_target_properties(
    bayan PROPERTIES 
    CXX_STANDARD 20 
    CXX_STANDARD_REQUIRED ON
)


target_link_libraries(
    bayan
    ${Boost_LIBRARIES}
)

target_include_directories(
    bayan
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include 
)


# set compile options
if (MSVC)
    target_compile_options(
        bayan 
        PRIVATE
        /W4
    )
else ()
    target_compile_options(
        bayan 
        PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()




### Deb pkg ###
install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)