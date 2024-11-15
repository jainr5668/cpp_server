cmake_minimum_required(VERSION 3.10)
project(CppServerExample)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
# find_package(tinyxml2 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(src/fw/common)
add_subdirectory(src/fw/endpoints)
add_subdirectory(src/fw/services)
add_subdirectory(src/router)
add_subdirectory(src/server)
# Main executable
add_executable(server src/main.cpp)
# Link libraries
target_link_libraries(server
services_lib
router_lib
endpoints_lib
common_lib
server_lib
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS}/**/*)
include_directories(${GTEST_INCLUDE_DIRS}/**/**/*)
include_directories(${GTEST_INCLUDE_DIRS}/**/**/**/*)