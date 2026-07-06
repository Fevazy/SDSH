cmake_minimum_required(VERSION 3.15)
project(SDSH VERSION 0.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED ON)

set(SDSH_SOURCES
    src/alloc.c
)

set(SDSH_PUBLIC_HEADERS include/SDSH.h)

add_library(SDSH STATIC ${SDSH_SOURCES} )
target_include_directories(SDSH
    INTERFACE include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
