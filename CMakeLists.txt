cmake_minimum_required(VERSION 3.15)
project(SDSH VERSION 0.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

option(SDSH_BUILD_TESTS "Build tests" ON)

set(SDSH_SOURCES
    src/alloc.c
    src/archetype.c
    src/component.c
    src/entity.c
    src/range.c
    src/system.c
    src/world.c
)

set(SDSH_PUBLIC_HEADERS
    include/sdsh.h
)


add_library(sdsh STATIC ${SDSH_SOURCES} )
target_include_directories(sdsh
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(SDSH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
