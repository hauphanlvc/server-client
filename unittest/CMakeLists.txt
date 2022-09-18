cmake_minimum_required(VERSION 3.10)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})

# Link everything together
# add_executable(ut_server_CreateSocket_test ut_server_CreateSocket.cpp ../src/server.cpp)
# add_executable(ut_server_connectToClients_test ut_server_connectToClients.cpp ../src/server.cpp)
add_executable(ut_client_sendName_test ../unittest/ut_client_sendName.cpp ../src/client.cpp)
add_executable(ut_client_clientTest_test ut_client_clientTest.cpp ../src/client.cpp)

# Add target link libraries
# target_link_libraries(ut_server_CreateSocket_test ${GTEST_LIBRARIES} pthread)
# target_link_libraries(ut_server_connectToClients_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(ut_client_sendName_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(ut_client_clientTest_test ${GTEST_LIBRARIES} pthread)
