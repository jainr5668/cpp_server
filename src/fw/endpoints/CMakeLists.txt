add_subdirectory(feature1)
add_subdirectory(Authentication)
add_subdirectory(Todo)

add_library(endpoints_lib INTERFACE)


target_link_libraries(endpoints_lib 
    INTERFACE feature1_lib router_lib common_lib
    INTERFACE authentication_lib
    INTERFACE todo_lib
)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/**/*)
include_directories(${GTEST_INCLUDE_DIRS}/**/**/*)