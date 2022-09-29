cmake_minimum_required(VERSION 3.9)

project(game VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE helloworld_SRC
     "src/*.hpp"
     "lib/*.hpp"
     "src/*.cpp"
     "lib/libmylib.a"
)

foreach (file ${helloworld_SRC})
    set(MYFILE_DIR)
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

file(GLOB_RECURSE rb_rpdb_src "lib/")
message(STATUS "headers: ${rb_rpdb_src} ")

include_directories("./SFML/include")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_LIB_DIR "./SFML/lib")

IF (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    link_directories(${SFML_LIB_DIR})
ENDIF()

add_executable(game ${helloworld_SRC})

message(STATUS /home/ruru/Desktop/epitech/perso/spriteCreator/lib/libmylib.a)

target_link_libraries(game ${CMAKE_SOURCE_DIR}/lib/libmylib.a)

if (WIN32)
    target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-network sfml-audio opengl32 winmm gdi32)
else ()
    target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
endif ()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
