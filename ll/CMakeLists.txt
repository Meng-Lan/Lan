cmake_minimum_required(VERSION 3.2)

project(net_ll)

#set(CMAKE_BUILD_TYPE "Debug" )

add_executable(
    ll
    control.cpp
    event.cpp
    epoll.cpp
    listener.cpp
    loop.cpp
    tcp_connection.cpp
    connector.cpp
    server.cpp
)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -pthread -DDEBUG -O2  ${CMAKE_CXX_FLAGS}")
    message(STATUS ${CMAKE_CXX_FLAGS})   
endif(CMAKE_COMPILER_IS_GNUCXX)

