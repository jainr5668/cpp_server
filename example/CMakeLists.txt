cmake_minimum_required(VERSION 3.16)
project(ServerExample)

# Adding CppServer directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../cppServer ${CMAKE_CURRENT_BINARY_DIR}/cppServer_build)

# Add additional sub directories as needed.
add_subdirectory(src/endpoint)

add_executable(exampleCppServer main.cpp)
target_link_libraries(exampleCppServer cppServer_lib exampleEndpoints_lib pthread)
