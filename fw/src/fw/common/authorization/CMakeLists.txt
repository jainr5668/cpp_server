add_library(authorization_lib
    src/authorization.cpp
)
include(FetchContent)
find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
    message(STATUS "Found OpenSSL ${OpenSSL_VERSION}")
    set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR})
    set(OPENSSL_INCLUDE_DIR ${OPENSSL_INCLUDE_DIR})
    set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_CRYPTO_LIBRARY})
endif()
FetchContent_Declare(
  jwt-cpp
  GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
  GIT_TAG v0.5.0
)
FetchContent_MakeAvailable(jwt-cpp)
target_include_directories(authorization_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(authorization_lib PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/pub
${CMAKE_CURRENT_SOURCE_DIR}/inc
)
# Link to common and other feature libraries if needed
target_link_libraries(authorization_lib common_lib server_lib services_lib jwt-cpp::jwt-cpp)
# target_link_libraries(authorization_lib PRIVATE jwt-cpp::jwt-cpp)
# Testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runAuthorizationTests test/authorization_test.cpp)
target_include_directories(runAuthorizationTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(runAuthorizationTests GTest::GTest GTest::Main authorization_lib)
add_test(NAME AythorizationTests COMMAND runAuthorizationTests)
