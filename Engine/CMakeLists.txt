cmake_minimum_required(VERSION 3.16)

# Ensure raylib is build as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)

set(PRODUCTION_BUILD OFF CACHE BOOL "Production build")

add_subdirectory(ThirdParty/raylib-6.0)
add_subdirectory(ThirdParty/json-3.12.0)
add_subdirectory(ThirdParty/raygui-4.0)
add_subdirectory(ThirdParty/entt-3.16.0)

# MY_SOURCES is defined to be a list of all the source files for my game
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp"
)

add_library(engine STATIC
        ${ENGINE_SOURCES}
)

if(PRODUCTION_BUILD)

    target_compile_definitions(engine PUBLIC
            RESOURCES_PATH="./Resources/"
            PRODUCTION_BUILD=1
    )

else()

    target_compile_definitions(engine PUBLIC
            RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/"
            PRODUCTION_BUILD=0
    )

endif()

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Src
)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/AssetManagement
)

target_include_directories(engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/Components
)

target_link_libraries(engine PUBLIC
        raylib_static
        nlohmann_json
        raygui
        EnTT
)