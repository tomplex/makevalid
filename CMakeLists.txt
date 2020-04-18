cmake_minimum_required(VERSION 3.15)
project(makevalid C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_C_STANDARD 11)

add_executable(
        makevalid
        src/main.c
        src/config.c
        src/config.h)


# Many thanks to
# https://github.com/valhalla/valhalla/blob/master/cmake/FindGEOS.cmake
find_path( GEOS_INCLUDE_DIR geos/geom/Geometry.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${GEOS_DIR}/include
        /usr/include
        /usr/local/include
        /usr/local/ossim/include )

# Find GEOS library:
find_library( GEOS_LIB NAMES geos
        PATHS
        ${CMAKE_INSTALL_PREFIX}/lib
        ${GEOS_DIR}/lib
        /usr/lib64
        /usr/lib
        /usr/local/lib
        /usr/local/ossim/lib )

# Find GEOS C library:
find_library( GEOS_C_LIB NAMES geos_c
        PATHS
        ${CMAKE_INSTALL_PREFIX}/lib
        ${GEOS_DIR}/lib
        /usr/lib64
        /usr/lib
        /usr/local/lib
        /usr/local/ossim/lib )

# Set the GEOS_LIBRARY:
if( GEOS_LIB AND GEOS_C_LIB )
    set( GEOS_LIBRARY ${GEOS_LIB} ${GEOS_C_LIB} CACHE STRING INTERNAL )
endif(GEOS_LIB AND GEOS_C_LIB )

#---
# This function sets GEOS_FOUND if variables are valid.
#---
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args( GEOS DEFAULT_MSG
        GEOS_LIBRARY
        GEOS_INCLUDE_DIR )

add_library(GEOS::GEOS INTERFACE IMPORTED)
if( GEOS_FOUND )
    if( NOT GEOS_FIND_QUIETLY )
        message( STATUS "Found GEOS..." )
    endif( NOT GEOS_FIND_QUIETLY )

    set_target_properties(GEOS::GEOS PROPERTIES
            INTERFACE_LINK_LIBRARIES "${GEOS_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${GEOS_INCLUDE_DIR}")
else( GEOS_FOUND )
    if( NOT GEOS_FIND_QUIETLY )
        message( WARNING "Could not find GEOS" )
    endif( NOT GEOS_FIND_QUIETLY )
endif( GEOS_FOUND )

if( NOT GEOS_FIND_QUIETLY )
    message( STATUS "GEOS_INCLUDE_DIR=${GEOS_INCLUDE_DIR}" )
    message( STATUS "GEOS_LIBRARY=${GEOS_LIBRARY}" )
endif( NOT GEOS_FIND_QUIETLY )

target_link_libraries(makevalid ${GEOS_C_LIB})
target_include_directories(makevalid PUBLIC ${GEOS_INCLUDE_DIR})
