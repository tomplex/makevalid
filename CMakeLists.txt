cmake_minimum_required(VERSION 3.15)
project(makevalid C)

set(CMAKE_C_STANDARD 11)

add_executable(makevalid src/main.c src/config.c src/config.h)

#target_link_libraries(makevalid /usr/local/geos/3.8.1/lib/libgeos_c.1.dylib)
#target_include_directories(makevalid PUBLIC /usr/local/geos/3.8.1/include)
target_link_libraries(makevalid /usr/local/lib)
target_include_directories(makevalid PUBLIC /usr/local/include)
