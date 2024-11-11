# Add the library
add_library(vfsService_lib
    src/VfsService.cpp src/VfsServiceData.cpp src/node.cpp
)

# Set include directories for the library
target_include_directories(vfsService_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(vfsService_lib common_lib server_lib)

# Add the test executable
add_executable(vfsService_lib_test
    test/VfsServiceTest.cpp
    test/VfsServiceDataTest.cpp
)

# Set include directories for the test
target_include_directories(vfsService_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(vfsService_lib_test PUBLIC vfsService_lib common_lib server_lib GTest::GTest GTest::Main gmock pthread)

# Enable testing
enable_testing()

# Add the test
add_test(NAME vfsServiceTest COMMAND vfsService_lib_test)