cmake_minimum_required(VERSION 3.16)

project(editor)

add_executable(editor app.rc)

set_property(TARGET editor PROPERTY CXX_STANDARD 17)

target_compile_definitions(editor PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties(editor PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile Editor"
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ThirdParty/imgui-docking)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ThirdParty/rlimgui)


add_library(visit_struct INTERFACE)

target_include_directories(visit_struct INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/visit_struct-1.2.0
)

# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Src/*.cpp")

target_sources(editor PRIVATE ${MY_SOURCES})

target_link_libraries(editor PRIVATE engine imgui rlimgui visit_struct)