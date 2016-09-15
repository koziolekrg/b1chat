cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

project(b1comm)

find_package(Threads)

set(sources 
	"main.cpp"
	"src/client.cpp"
	"src/receive.cpp"

)
include_directories("../include/" "./include/" "./interface")

add_executable(${PROJECT_NAME} "include/client.h" "include/receive.h" ${sources})

target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
