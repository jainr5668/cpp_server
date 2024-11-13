# Add the library
add_library(commonService_lib
    src/CommonService.cpp src/utilityService.cpp
)

# Set include directories for the library
target_include_directories(commonService_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(commonService_lib common_lib server_lib)

# Add the test executable
add_executable(commonService_lib_test
    test/CommonServiceTest.cpp
)

# Set include directories for the test
target_include_directories(commonService_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(commonService_lib_test PUBLIC commonService_lib common_lib server_lib GTest::GTest GTest::Main)

# Enable testing
enable_testing()

# Add the test
add_test(NAME CommonServiceTest COMMAND commonService_lib_test)