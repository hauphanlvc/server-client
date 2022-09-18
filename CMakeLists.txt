cmake_minimum_required(VERSION 3.10)

# set the project name
project(ChatServer)
find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# add the executable
add_executable(client src/client.cpp src/client_main.cpp)
target_link_libraries(client PRIVATE Threads::Threads)

# server ralated
# add_executable(server src/server.cpp src/server_main.cpp)
# target_link_libraries(server PRIVATE mysqlcppconn)
# include_directories(/usr/include/mysql-cppconn-8/jdbc)