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
