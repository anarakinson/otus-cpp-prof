cmake_minimum_required(VERSION 3.5)


project(ip_filter)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

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
set_target_properties(
    ip_filter_test 
    PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR} 
)

# set include directories
target_include_directories(
    ip_filter
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
)

# link libraries
target_link_libraries(
    ip_filter_test
    ${Boost_LIBRARIES}
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


enable_testing()

add_test(test ip_filter_test)

