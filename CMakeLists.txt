cmake_minimum_required(VERSION 3.31)
project(echo_server)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH"/opt/homebrew")

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(echo_server main.cpp
        server.cpp
        server.h)
target_link_libraries(echo_server PRIVATE Boost::system)