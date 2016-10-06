cmake_minimum_required (VERSION 2.6)
add_definitions("-Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++0x")

project(b1chat_client)

add_compile_options(-std=c++0x)

find_package(Threads)

set(sources 
	"src/main.cpp"
	"src/client.cpp"
        "src/socket.cpp"
)
include_directories("../include/" "./include/" "./interface")

add_executable(${PROJECT_NAME} "include/client.h" "include/socket.h" ${sources})

target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
