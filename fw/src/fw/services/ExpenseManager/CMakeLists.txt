add_subdirectory(
    subServices/ExpenseManagerAccountsService
)

# Add the library
add_library(expenseManagerService_lib
    src/ExpenseManagerService.cpp
    src/ExpenseManagerCategoriesService.cpp
    src/ExpenseManagerReportsService.cpp
    src/ExpenseManagerTagsService.cpp
    src/ExpenseManagerTransactionsService.cpp
)

# Set include directories for the library
target_include_directories(expenseManagerService_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)


target_link_libraries(expenseManagerService_lib PUBLIC
    common_lib
    server_lib
    commonService_lib
    INTERFACE expenseManagerAccountsService_lib
)

# Add the test executable
add_executable(expenseManagerService_lib_test
    test/ExpenseManagerServiceTest.cpp
)

# Set include directories for the test
target_include_directories(expenseManagerService_lib_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/testResources)

# Link the test executable with the library
target_link_libraries(expenseManagerService_lib_test PUBLIC expenseManagerService_lib common_lib server_lib GTest::GTest GTest::Main gmock pthread)

# Enable testing
enable_testing()

# Add the test
add_test(NAME ExpenseManagerServiceTest COMMAND expenseManagerService_lib_test)
