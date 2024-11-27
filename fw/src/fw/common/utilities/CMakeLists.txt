
add_library(utilities_lib
   utils.cpp
)
target_include_directories(utilities_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runUtilitiesTests utils_test.cpp)
target_link_libraries(runUtilitiesTests GTest::GTest GTest::Main utilities_lib)
add_test(NAME UtilitiesTests COMMAND runUtilitiesTests)
