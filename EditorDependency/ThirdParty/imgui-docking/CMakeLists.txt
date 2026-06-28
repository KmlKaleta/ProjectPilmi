cmake_minimum_required(VERSION 3.10)
project(imgui)

add_library(imgui)
target_sources(imgui PRIVATE
"imgui/imgui.cpp"
"imgui/imgui_demo.cpp"
"imgui/imgui_draw.cpp"
"imgui/imgui_tables.cpp"
"imgui/imgui_widgets.cpp"
"imgui/misc/cpp/imgui_stdlib.cpp"
)


message("imgui")
message("imgui")

target_include_directories(imgui PUBLIC
        imgui
)