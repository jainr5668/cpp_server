add_subdirectory(feature1_service)
add_subdirectory(AuthenticationService)
add_subdirectory(Todo)

add_library(services_lib INTERFACE)

target_link_libraries(services_lib
    INTERFACE feature1_service_lib
    INTERFACE authenticationService_lib
    INTERFACE todoService_lib
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/**/*)
include_directories(${GTEST_INCLUDE_DIRS}/**/**/*)