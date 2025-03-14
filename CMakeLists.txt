cmake_minimum_required(VERSION 3.28)
project(ProjectName)

add_subdirectory(cppServer)

add_executable(cppServerout main.cpp)
target_link_libraries(cppServerout cppServer_lib)