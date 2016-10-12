cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

project(client_unittest)

add_compile_options(-std=c++0x)

set(sources 
	"main.cpp"
	"../src/client.cpp"
        "../src/socket.cpp"

)
include_directories(BEFORE ${GTEST_INCLUDE_DIRS})
include_directories(BEFORE ${GMOCK_INCLUDE_DIRS})

find_package(GTest REQUIRED)

include_directories("../include/" "./include/" "../interface")

add_executable(${PROJECT_NAME} "../include/client.h" "../include/socket.h" "./mocksocket.h"${sources})

target_link_libraries(client_unittest ${GTEST_BOTH_LIBRARIES} pthread gtest gmock)

