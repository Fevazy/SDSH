cmake_minimum_required(VERSION 3.15)
project(sdsh VERSION 0.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_STANDARD_REQUIRED ON)

set(SDSH_SOURCES
    #TODO
)

set(SDSH_PUBLIC_HEADERS include/SDSH.h)

add_library(sdsh STATIC ${SOURCES} )
target_include_directories(sdsh
    INTERFACE include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
