cmake_minimum_required (VERSION 2.8)
add_definitions("-Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++0x")

project(b1chat_server)

add_compile_options(-std=c++0x)

set(sources 
	"src/main.cpp"
	"src/server.cpp"
	"src/user.cpp"
	"src/group.cpp"
	"src/priv.cpp"
        "src/login.cpp"
	"src/socket.cpp"
)

include_directories("../include/" "./include/" "./interface/")

add_executable(${PROJECT_NAME} "include/server.h" "include/user.h" "include/group.h" "include/priv.h" "include/login.h" "include/socket.h" ${sources})

