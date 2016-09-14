cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

project(b1comm)

set(sources 
	"main.cpp"
	"src/client.cpp"

)
include_directories("../include/" "./include/" "./interface")

add_executable(${PROJECT_NAME} "include/client.h" ${sources})

