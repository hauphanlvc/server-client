cmake_minimum_required(VERSION 3.10)

# set the project name
project(ChatServer)
# find_package(Threads REQUIRED)
# find_package(Curses REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CURSES_INCLUDE_DIR})

# add the executable
# add_executable(client src/client.cpp src/client_main.cpp)
# target_link_libraries(client PRIVATE Threads::Threads ${CURSES_LIBRARIES})

# server ralated

add_executable(server ../../src/server.cpp ../../src/server_main.cpp)
target_link_libraries(server PRIVATE mysqlcppconn)
