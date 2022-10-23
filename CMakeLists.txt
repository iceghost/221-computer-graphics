project(contraption)
cmake_minimum_required(VERSION 3.24)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED TRUE)

IF(MSVC)
  add_definitions(-D_USE_MATH_DEFINES)
ENDIF()

add_executable(main main.cpp)
add_subdirectory(mesh)
add_subdirectory(supportclasses)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(main PRIVATE mesh supportclasses OpenGL::GL OpenGL::GLU GLUT::GLUT)
