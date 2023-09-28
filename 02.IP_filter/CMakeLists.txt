cmake_minimum_required(VERSION 3.5)


project(ip_filter)

find_package(GTest CONFIG REQUIRED)


# sources
add_executable(ip_filter src/ip_filter.cpp)
add_executable(ip_filter_test test/test.cpp)


# set target properties
set_target_properties(
    ip_filter ip_filter_test
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
target_include_directories(
    ip_filter_test
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
)

# link libraries
target_link_libraries(
    ip_filter_test 
    PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
)


# set compile options
if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_test PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_test PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


### Tests ###
enable_testing()

add_test(ip_filter_test ip_filter_test)



### Deb pkg release ###
set(PATCH_VERSION "1" CACHE INTERNAL "IP Filter")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)