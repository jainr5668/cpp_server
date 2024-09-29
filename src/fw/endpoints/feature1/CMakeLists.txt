add_library(feature1_lib
    src/feature1.cpp
)
target_include_directories(feature1_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(feature1_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Link to common and other feature libraries if needed
target_link_libraries(feature1_lib common_lib server_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runFeature1Tests test/feature1_test.cpp)
target_include_directories(runFeature1Tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runFeature1Tests GTest::GTest GTest::Main feature1_lib)
add_test(NAME Feature1Tests COMMAND runFeature1Tests)
