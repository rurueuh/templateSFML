cmake_minimum_required(VERSION 3.9)

project(mylib VERSION 1.0.1 DESCRIPTION "mylib description")

add_library(mylib STATIC
    Collision/Collision.cpp
    Collision/CollisionPrivate.cpp
)

set_target_properties(mylib PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(mylib PROPERTIES SOVERSION 1)

target_include_directories(mylib PRIVATE .)
target_link_libraries(mylib sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

execute_process(COMMAND mv libmylib.a ../)
