
add_library(logging_lib
   logger.cpp
   logger.h
)
# add_library(Logger SHARED logger.cpp)
# Find and link Threads library
find_package(Threads REQUIRED)
target_link_libraries(logging_lib PRIVATE Threads::Threads)
target_include_directories(logging_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runLoggingTests logger_test.cpp)
target_link_libraries(runLoggingTests GTest::GTest GTest::Main logging_lib)
add_test(NAME LoggingTests COMMAND runLoggingTests)
