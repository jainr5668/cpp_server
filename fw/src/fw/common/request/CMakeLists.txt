
add_library(request_lib
   request.cpp
)
target_include_directories(request_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(request_lib utilities_lib authorization_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runrequestTests request_test.cpp)
target_link_libraries(runrequestTests GTest::GTest GTest::Main request_lib)
add_test(NAME requestTests COMMAND runrequestTests)
