cmake_minimum_required(VERSION 3.10)
project(use_libraw)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBRAW REQUIRED libraw)

include_directories(${LIBRAW_INCLUDE_DIRS})
link_directories(${LIBRAW_LIBRARY_DIRS})
add_definitions(${LIBRAW_CFLAGS_OTHER})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBRAW_LIBRARIES})
