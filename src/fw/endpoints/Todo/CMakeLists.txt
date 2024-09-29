add_library(todo_lib
    src/TodoEndpoint.cpp
)
target_include_directories(todo_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(todo_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Link to common and other feature libraries if needed
target_link_libraries(todo_lib common_lib server_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runTodoTests test/TodoEndpointTest.cpp)
target_include_directories(runTodoTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runTodoTests GTest::GTest GTest::Main todo_lib)
add_test(NAME TodoTests COMMAND runTodoTests)
