add_library(vfs_lib
    src/VfsEndpoint.cpp
)
target_include_directories(vfs_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vfs_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Link to common and other feature libraries if needed
target_link_libraries(vfs_lib common_lib server_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runVfsTests test/VfsEndpointTest.cpp)
target_include_directories(runVfsTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runVfsTests GTest::GTest GTest::Main vfs_lib)
add_test(NAME VfsTests COMMAND runVfsTests)
