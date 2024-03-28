cmake_minimum_required(VERSION 3.12)


### set version
set(PATCH_VERSION "1" CACHE INTERNAL "Bulk")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(fashion_mnist VERSION ${PROJECT_VERSION})


### find g-test
find_package(GTest CONFIG REQUIRED)


######################
add_executable(
    fashion_mnist 
    src/main.cpp 
    src/tf_classifier.cpp
)
add_executable(
    tests 
    tests/test_tf.cpp
    src/tf_classifier.cpp
)

######################
if(MSVC)
    ### SET PATH TO TENSORFLOW 'C'-API LIBRARY:
    set(TF_PATH $ENV{CXX_TF_LIBRARY}/gpu)
    # set(TF_PATH "${CMAKE_SOURCE_DIR}/../../tensorflow/gpu")
    message("${TF_PATH}")
    
    ### headers
    target_include_directories(
        fashion_mnist 
        PRIVATE
        "${TF_PATH}/include/"
    )
    target_include_directories(
        tests 
        PRIVATE
        "${TF_PATH}/include/"
    )

    ### link library
    target_link_libraries(
        fashion_mnist PRIVATE 
        "${TF_PATH}/lib/tensorflow.lib"
    )
    target_link_libraries(
        tests PRIVATE 
        "${TF_PATH}/lib/tensorflow.lib"
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
    )

    add_custom_target(
        copy_dll
        COMMAND ${CMAKE_COMMAND} -E copy ${TF_PATH}/lib/tensorflow.dll ${CMAKE_BINARY_DIR}/Debug/tensorflow.dll
    )
    add_dependencies(fashion_mnist copy_dll)
else()
    target_link_libraries(
        fashion_mnist PRIVATE
        tensorflow
    )
    target_link_libraries(
        tests PRIVATE 
        tensorflow
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
    )
endif()


####################
include_directories(
    "include"
)


set_target_properties(
    fashion_mnist PROPERTIES 
    SXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
set_target_properties(
    tests PROPERTIES 
    SXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


# set compile options
if (MSVC)
    target_compile_options(fashion_mnist PRIVATE
        # /W4
    )
    target_compile_options(tests PRIVATE
        # /W4
    )
else ()
    target_compile_options(fashion_mnist PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(tests PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()




### Deb pkg release ###
install(TARGETS fashion_mnist RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)


enable_testing()
add_test(AllTestsInMain tests)