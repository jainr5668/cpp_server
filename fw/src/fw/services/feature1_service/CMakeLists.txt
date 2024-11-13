# Add the library
add_library(feature1_service_lib
    src/feature1_service.cpp src/Feature1ServiceData.cpp
)

# Set include directories for the library
target_include_directories(feature1_service_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(feature1_service_lib common_lib server_lib)

# Add the test executable
add_executable(feature1_service_lib_test
    test/feature1_service_test.cpp
)

# Set include directories for the test
target_include_directories(feature1_service_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(feature1_service_lib_test PUBLIC feature1_service_lib common_lib server_lib GTest::GTest GTest::Main)

# Enable testing
enable_testing()

# Add the test
add_test(NAME Feature1ServiceTest COMMAND feature1_service_lib_test)