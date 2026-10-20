cmake_minimum_required(VERSION 3.21)
project(CourseProject LANGUAGES CXX)

# ------ Global compiler settings ------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Unified output directories: build/bin & build/lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Qt auto-process moc, uic & rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# If using MSVC: ensure encoding utf-8
if (MSVC)
    add_compile_options(/utf-8)
endif ()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(CourseProject
        src/main.cpp
)

target_link_libraries(CourseProject PRIVATE
        Qt6::Widgets
)
