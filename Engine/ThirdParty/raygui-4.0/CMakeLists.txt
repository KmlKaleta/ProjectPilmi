cmake_minimum_required(VERSION 3.11)
project(raygui)

add_library(raygui INTERFACE)

target_include_directories(raygui INTERFACE
        "src"
        "styles/dark"
)