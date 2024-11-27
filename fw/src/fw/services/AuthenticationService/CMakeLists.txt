# Add the library
add_library(authenticationService_lib
    src/AuthenticationService.cpp src/AuthenticationServiceeData.cpp
)

# Set include directories for the library
target_include_directories(authenticationService_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(authenticationService_lib common_lib server_lib)

# Add the test executable
add_executable(authenticationService_lib_test
    test/AuthenticationServiceTest.cpp
)

# Set include directories for the test
target_include_directories(authenticationService_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(authenticationService_lib_test PUBLIC authenticationService_lib common_lib server_lib GTest::GTest GTest::Main gmock pthread)

# Enable testing
enable_testing()

# Add the test
add_test(NAME AuthenticationServiceTest COMMAND authenticationService_lib_test)
