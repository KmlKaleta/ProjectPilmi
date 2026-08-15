cmake_minimum_required(VERSION 3.16)

project(engine)

# Ensure raylib is build as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)

#! ! ! ! ! ! !
#set this to ON instead of OFF to ship the game!
#basically this will change the RESOURCES_PATH to be the local path
#! ! ! ! ! ! !
#delete the out folder after changing if visual studio doesn't recognize the change
set(PRODUCTION_BUILD ON CACHE BOOL "Production build")

add_subdirectory(ThirdParty/raylib-6.0)
add_subdirectory(ThirdParty/json-3.12.0)
add_subdirectory(ThirdParty/raygui-4.0)
add_subdirectory(ThirdParty/entt-3.16.0)

# ==============================================================================
# CODE GENERATION STEP (Roslyn Style)
# ==============================================================================
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# 1. Create a custom target to execute the script
add_custom_target(RunCodegen ALL
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/Src/componentgen.py"
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/Src/spriteenumgen.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Src"
        COMMENT "Executing Python C++ source code generator..."
        VERBATIM
)

# 2. Force code generation to execute right now *during* the CMake configuration phase.
# This guarantees GeneratedComponents.h exists before file(GLOB_RECURSE) runs.
execute_process(
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/Src/componentgen.py"
        COMMAND Python3::Interpreter "${CMAKE_CURRENT_SOURCE_DIR}/Src/spriteenumgen.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Src"
)
# ==============================================================================


# MY_SOURCES is defined to be a list of all the source files for my game
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp"
)

add_library(engine STATIC
        ${ENGINE_SOURCES}
)

# 3. Make the engine library depend on the generator target
# This forces Python to re-scan files whenever you click 'Build' in your IDE
add_dependencies(engine RunCodegen)

add_library(visit_struct INTERFACE)

target_include_directories(visit_struct INTERFACE
        ThirdParty/visit_struct-1.2.0
)

if (PRODUCTION_BUILD)

    target_compile_definitions(engine PUBLIC
            RESOURCES_PATH="./Resources/"
            PRODUCTION_BUILD=1
    )

else ()

    target_compile_definitions(engine PUBLIC
            RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/"
            PRODUCTION_BUILD=0
    )

endif ()

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
        visit_struct
)