cmake_minimum_required(VERSION 3.5)

### set version
set(PATCH_VERSION "1" CACHE INTERNAL "Bulk")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(bulk_server VERSION ${PROJECT_VERSION})


### find boost
find_package(Boost COMPONENTS system program_options REQUIRED)
find_package(Threads)


######################
add_executable(
    bulk_server
    src/server.cpp 
)
add_executable(
    client
    src/client.cpp 
)

add_library(
    asynclib 
    asynclib/async.cpp
)


set_target_properties(
    bulk_server client asynclib
    PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    bulk_server 
    PRIVATE 
    asynclib 
    ${Boost_LIBRARIES}
)
target_link_libraries(
    client
    ${Boost_LIBRARIES}
)

# set compile options
if (MSVC)
    target_compile_options(asynclib PRIVATE
        # /W4
    )
    target_compile_options(client PRIVATE
        # /W4
    )
    target_compile_options(bulk_server PRIVATE
        # /W4
    )

else ()
    target_compile_options(asynclib PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(client PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(bulk_server PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()



### Deb pkg release ###
install(TARGETS bulk_server client RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)
