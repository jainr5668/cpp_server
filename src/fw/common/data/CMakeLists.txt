
add_library(data_lib
   src/Data.cpp
)
target_include_directories(data_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(data_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
)
target_link_libraries(data_lib LINK_PUBLIC sqlite3)
# target_link_libraries(data_lib sqlite3)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runDataTests test/DataTest.cpp)
target_include_directories(runDataTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runDataTests GTest::GTest GTest::Main data_lib)
add_test(NAME DataTests COMMAND runDataTests)
