cmake_minimum_required(VERSION 3.16)

project(game)

add_executable(game app.rc)

set_property(TARGET game PROPERTY CXX_STANDARD 17)

target_compile_definitions(game PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties(game PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile"
)

# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp")

target_sources(game PRIVATE ${MY_SOURCES})

target_link_libraries(game PRIVATE engine)