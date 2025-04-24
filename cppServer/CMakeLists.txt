add_library(cppServer_lib
    src/Authentication.cpp
    src/RequestContent.cpp
    src/ResponseContent.cpp
    src/Server.cpp
    src/Router.cpp
)

target_include_directories(cppServer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(cppServer_tests
    test/AuthenticationTest.cpp
    test/RequestContentTest.cpp
    test/ResponseContentTest.cpp
    test/ServerTest.cpp
    test/RouterTest.cpp
    test/main.cpp
)

target_link_libraries(cppServer_tests
    cppServer_lib
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)

add_test(NAME cppServer_tests COMMAND cppServer_tests)