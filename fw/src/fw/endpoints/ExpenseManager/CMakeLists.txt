add_library(expenseManager_lib
    src/ExpenseManagerEndpoint.cpp
    src/ExpenseManagerAccountsEndpoint.cpp
    src/ExpenseManagerCategoriesEndpoint.cpp
    src/ExpenseManagerTransactionsEndpoint.cpp
    src/ExpenseManagerTagsEndpoint.cpp
    src/ExpenseManagerReportsEndpoint.cpp
)
target_include_directories(expenseManager_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(expenseManager_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/..
)
# Link to common and other feature libraries if needed
target_link_libraries(expenseManager_lib common_lib server_lib services_lib)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runExpenseManagerEndpointTests test/ExpenseManagerEndpointTest.cpp)
target_include_directories(runExpenseManagerEndpointTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runExpenseManagerEndpointTests GTest::GTest GTest::Main expenseManager_lib)
add_test(NAME ExpenseManagerEndpointTests COMMAND runExpenseManagerEndpointTests)
