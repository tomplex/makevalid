cmake_minimum_required(VERSION 3.13)
project(makevalid C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(
        makevalid
        src/main.c
        src/config.c
        src/config.h)

if (GEOS_DIR)
    message(STATUS "Trying user-specified GEOS installation at ${GEOS_DIR}")
    find_path(GEOS_INCLUDE_DIR geos_c.h
            PATHS ${GEOS_DIR}/include
            NO_DEFAULT_PATH)
    find_library(GEOS_C_LIB geos_c
            PATHS ${GEOS_DIR}/lib
            NO_DEFAULT_PATH)
    find_path(GEOS_CONFIG geos-config
            PATHS ${GEOS_DIR}/bin
            NO_DEFAULT_PATH)
else(GEOS_DIR)
    find_path(GEOS_INCLUDE_DIR geos_c.h
            PATHS
            ${CMAKE_INSTALL_PREFIX}/include
            /usr/include
            /usr/local/include)
    find_library(GEOS_C_LIB NAMES geos_c
            PATHS
            ${CMAKE_INSTALL_PREFIX}/lib
            /usr/lib64
            /usr/lib
            /usr/local/lib)
    find_path(GEOS_CONFIG geos-config
            PATHS
            /usr/bin
            /usr/local/bin)
endif(GEOS_DIR)

if( GEOS_C_LIB AND GEOS_INCLUDE_DIR )
    message( STATUS "Found GEOS..." )
else( GEOS_C_LIB AND GEOS_INCLUDE_DIR )
    message( ERROR "Could not find GEOS" )
endif( GEOS_C_LIB AND GEOS_INCLUDE_DIR )

message( STATUS "GEOS_INCLUDE_DIR=${GEOS_INCLUDE_DIR}" )
message( STATUS "GEOS_LIBRARY=${GEOS_C_LIB}" )

# Check GEOS version to ensure >= 3.8
if (GEOS_CONFIG)
    message(STATUS "Found geos-config at ${GEOS_CONFIG}")
    execute_process(COMMAND ${GEOS_CONFIG}/geos-config --version OUTPUT_VARIABLE GEOS_VERSION)
    message(STATUS "GEOS Version: ${GEOS_VERSION}")
else (GEOS_CONFIG)
    message(ERROR "Could not find geos-config to check version")
endif(GEOS_CONFIG)

if (GEOS_VERSION STRLESS_EQUAL 3.8)
    message(ERROR "Makevalid requires GEOS >= 3.8")
endif(GEOS_VERSION STRLESS_EQUAL 3.8)

target_link_libraries(makevalid ${GEOS_C_LIB})
target_include_directories(makevalid PUBLIC ${GEOS_INCLUDE_DIR})
