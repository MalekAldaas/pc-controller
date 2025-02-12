#CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(Server)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(COMMANDS_SRC_DIR ${SRC_DIR}/commands)
set(COMMANDS_INCLUDE_DIR ${INCLUDE_DIR}/commands)

file(GLOB SERVER_SOURCES ${SRC_DIR}/*.cpp)
file(GLOB COMMAND_SOURCES ${COMMANDS_SRC_DIR}/*.cpp)
file(GLOB SERVER_HEADERS ${INCLUDE_DIR}/*.h)
file(GLOB COMMAND_HEADERS ${COMMANDS_INCLUDE_DIR}/*.h)


add_executable(Server server.cpp ${SERVER_SOURCES} ${COMMAND_SOURCES})

target_include_directories(Server PRIVATE ${INCLUDE_DIR} ${COMMANDS_INCLUDE_DIR})


