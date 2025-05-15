cmake_minimum_required(VERSION 3.10)
project(dng_to_gimi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")


# Find LibRaw
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBRAW REQUIRED libraw)

# Find libheif
pkg_check_modules(LIBHEIF REQUIRED libheif)

include_directories(
  ${LIBRAW_INCLUDE_DIRS}
  ${LIBHEIF_INCLUDE_DIRS}
)

link_directories(
  ${LIBRAW_LIBRARY_DIRS}
  ${LIBHEIF_LIBRARY_DIRS}
)

add_definitions(
  ${LIBRAW_CFLAGS_OTHER}
  ${LIBHEIF_CFLAGS_OTHER}
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${LIBRAW_LIBRARIES}
  ${LIBHEIF_LIBRARIES}
)
