cmake_minimum_required(VERSION 3.16)

project(editor_dependency)

add_subdirectory(ThirdParty/imgui-docking)
add_subdirectory(ThirdParty/rlimgui)
add_subdirectory(ThirdParty/glm-1.0.3)

file(GLOB_RECURSE EDITOR_DEPENDENCY_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp"
)

add_library(editor_dependency STATIC
        ${EDITOR_DEPENDENCY_SOURCES}
)

add_library(imguizmo ThirdParty/ImGuizmo-1.10/src/ImGuizmo.cpp)

target_include_directories(imguizmo PUBLIC ThirdParty/ImGuizmo-1.10)

target_link_libraries(imguizmo PUBLIC imgui)

target_include_directories(editor_dependency PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_link_libraries(editor_dependency PUBLIC engine imgui imguizmo rlimgui glm)