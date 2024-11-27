add_subdirectory(data)
add_subdirectory(logging)
add_subdirectory(utilities)
add_subdirectory(response)
add_subdirectory(request)
add_subdirectory(authorization)

add_library(common_lib INTERFACE)

target_link_libraries(common_lib
    INTERFACE data_lib
    INTERFACE logging_lib
    INTERFACE utilities_lib
    INTERFACE response_lib
    INTERFACE request_lib
    INTERFACE authorization_lib
)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/**/*)
include_directories(${GTEST_INCLUDE_DIRS}/**/**/*)
