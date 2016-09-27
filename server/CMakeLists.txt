cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(b1comm)

add_compile_options(-std=c++0x)

set(sources 
	"main.cpp"
	"src/server.cpp"
	"src/user.cpp"
	"src/group.cpp"
	"src/priv.cpp"
        "src/login.cpp"
)

include_directories("../include/" "./include/" "./interface")

add_executable(${PROJECT_NAME} "include/server.h" "include/user.h" "include/group.h" "include/priv.h" "include/login.h" ${sources})

