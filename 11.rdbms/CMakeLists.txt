cmake_minimum_required(VERSION 3.5)

### set version
set(PATCH_VERSION "2" CACHE INTERNAL "Bulk")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

### start project
project(rdbms VERSION ${PROJECT_VERSION})


### find boost and sqlite
# find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(Boost COMPONENTS system program_options REQUIRED)
find_package(Threads)


######################
add_executable(
    join_server
    src/server.cpp 
    src/database.cpp 
)
add_executable(
    client
    src/client.cpp 
)


### properties
set_target_properties(
    join_server
    PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
set_target_properties(
    join_server
    PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)


### include
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)


### libraries
target_link_libraries(
    join_server PRIVATE 
    # unofficial::sqlite3::sqlite3
    ${Boost_LIBRARIES}
)
target_link_libraries(
    client PRIVATE
    ${Boost_LIBRARIES}
)

# set compile options
if (MSVC)
    target_compile_options(join_server PRIVATE
        # /W4
    )
    target_compile_options(client PRIVATE
        # /W4
    )
else ()
    target_compile_options(join_server PRIVATE
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
endif()



### Deb pkg release ###
install(TARGETS join_server client RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)


include(CPack)

