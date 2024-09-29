add_library(authentication_lib
    src/AuthenticationEndpoint.cpp
)
target_include_directories(authentication_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(authentication_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Link to common and other feature libraries if needed
target_link_libraries(authentication_lib common_lib server_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runAuthenticationTests test/AuthenticationEndpointTest.cpp)
target_include_directories(runAuthenticationTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runAuthenticationTests GTest::GTest GTest::Main authentication_lib)
add_test(NAME AuthenticationTests COMMAND runAuthenticationTests)
