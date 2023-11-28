# to run: cmake . && make

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -std=c++17 -Wall -Wextra -Werror)
project(game VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE OpenGL::GL GLUT::GLUT)
