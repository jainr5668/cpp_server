
add_library(response_lib
   response.cpp
)
target_include_directories(response_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runresponseTests response_test.cpp)
target_link_libraries(runresponseTests GTest::GTest GTest::Main response_lib)
add_test(NAME responseTests COMMAND runresponseTests)
