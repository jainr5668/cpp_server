add_library(cppServer_lib
    src/Authentication.cpp
    src/Authorization.cpp
    src/logger.cpp
    src/RequestContent.cpp
    src/ResponseContent.cpp
    src/Router.cpp
    src/Server.cpp
)
include(FetchContent)
FetchContent_Declare(
  jwt-cpp
  GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
  GIT_TAG v0.5.0
)
FetchContent_MakeAvailable(jwt-cpp)

target_include_directories(cppServer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
)

target_link_libraries(cppServer_lib jwt-cpp::jwt-cpp)
