add_library(router_lib
    src/router.cpp
)
target_include_directories(router_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# Link to common and other feature libraries if needed
target_link_libraries(router_lib common_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runrouterTests test/router_test.cpp)
target_include_directories(runrouterTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runrouterTests GTest::GTest GTest::Main router_lib)
add_test(NAME routerTests COMMAND runrouterTests)