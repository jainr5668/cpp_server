add_library(server_lib
    src/server.cpp
)
target_include_directories(server_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR})
# Link to common and other feature libraries if needed
target_link_libraries(server_lib common_lib router_lib endpoints_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runserverTests test/server_test.cpp)
target_include_directories(runserverTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runserverTests GTest::GTest GTest::Main server_lib)
add_test(NAME serverTests COMMAND runserverTests)