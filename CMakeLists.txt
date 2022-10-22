cmake_minimum_required(VERSION 3.24)
set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED TRUE)

project(contraption)

add_executable(main main.cpp)

add_subdirectory(mesh)
add_subdirectory(supportclasses)
find_library(GL NAMES libGL)
find_library(GLU NAMES libGLU)
find_library(glut NAMES libglut)
list(APPEND EXTRA_LIBS )
target_link_libraries(main PRIVATE mesh supportclasses GL GLU glut)
