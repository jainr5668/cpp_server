# Add the library
add_library(expenseManagerAccountsService_lib
    src/ExpenseManagerAccountsService.cpp
    src/ExpenseManagerAccountsServiceData.cpp
)

# Set include directories for the library
target_include_directories(expenseManagerAccountsService_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(expenseManagerAccountsService_lib common_lib server_lib commonService_lib)

# Add the test executable
add_executable(expenseManagerAccountsService_lib_test
    test/ExpenseManagerAccountsServiceTest.cpp
)

# Set include directories for the test
target_include_directories(expenseManagerAccountsService_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(expenseManagerAccountsService_lib_test PUBLIC expenseManagerAccountsService_lib common_lib server_lib GTest::GTest GTest::Main gmock pthread)

# Enable testing
enable_testing()

# Add the test
add_test(NAME ExpenseManagerAccountsServiceTest COMMAND expenseManagerAccountsService_lib_test)
