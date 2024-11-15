# to run: cmake . && make

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -std=c++17 -Wall -Wextra -Werror -Wunused-variable -W)
project(game VERSION 1.0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(Vector2d "src/lib/Vector2d.h")
set(EntityHandler "src/lib/EntityHandler.h" "src/lib/EntityHandler.cpp")
set(Entity "src/lib/Entity.h" "src/lib/Entity.cpp")
set(Controller "src/lib/Controller.h")
set(TimerHandler "src/lib/TimerHandler.h")
set(Difficulty "src/lib/Difficulty.h")

include_directories(include)

add_executable(main src/main.cpp ${TimerHandler} ${Controller} ${Vector2d} ${Entity} ${EntityHandler} ${Difficulty})
target_include_directories(main PUBLIC src/lib/)
target_link_libraries(main PRIVATE OpenGL::GL GLUT::GLUT)
