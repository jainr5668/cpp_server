cmake_minimum_required(VERSION 3.28)
project(ServerExample)

add_subdirectory(src)

add_executable(exampleCppServer main.cpp)
target_link_libraries(cppServerout cppServer_lib)