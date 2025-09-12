add_library(commonTypes_lib inc/jsonType.h)

target_include_directories(commonTypes_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/pub
)

target_link_libraries(commonTypes_lib cppServer_lib)
