add_library(exampleEndpoints_lib
    src/Endpoint1.cpp
)

target_include_directories(exampleEndpoints_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
)

target_link_libraries(exampleEndpoints_lib cppServer_lib commonTypes_lib)
