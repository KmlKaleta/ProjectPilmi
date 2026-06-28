cmake_minimum_required(VERSION 3.16)

project(editor_dependency)

add_subdirectory(ThirdParty/imgui-docking)
add_subdirectory(ThirdParty/rlimgui)

file(GLOB_RECURSE EDITOR_DEPENDENCY_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp"
)

add_library(editor_dependency STATIC
        ${EDITOR_DEPENDENCY_SOURCES}
)

add_library(visit_struct INTERFACE)

target_include_directories(visit_struct INTERFACE
        ThirdParty/visit_struct-1.2.0
)

target_include_directories(editor_dependency PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_link_libraries(editor_dependency PUBLIC engine imgui rlimgui visit_struct)