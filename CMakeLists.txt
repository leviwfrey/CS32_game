# to run: cmake . && make

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -std=c++17 -Wall -Wextra -Werror -Wunused-variable -W)
project(game VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(Draw "src/lib/Draw.h")
set(Point "src/lib/Point.h")

include_directories(include)

add_executable(main src/main.cpp ${Draw} ${Point})
target_include_directories(main PUBLIC src/lib/)
target_link_libraries(main PRIVATE OpenGL::GL GLUT::GLUT)
