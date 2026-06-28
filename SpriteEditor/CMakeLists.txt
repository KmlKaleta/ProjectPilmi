cmake_minimum_required(VERSION 3.16)

project(sprite_editor)

add_executable(sprite_editor app.rc)

set_property(TARGET sprite_editor PROPERTY CXX_STANDARD 17)

if (MSVC) # If using the VS compiler...

    target_compile_definitions(sprite_editor PUBLIC _CRT_SECURE_NO_WARNINGS)

    if (PRODUCTION_BUILD)
        #YOU CAN REMOVE THE CONSOLE WITH THIS LINE!
        set_target_properties(sprite_editor PROPERTIES
                LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" #no console
        )
    endif ()

elseif (MINGW) # Windows / MinGW GCC/Clang
    if (PRODUCTION_BUILD)
        # Remove console on Windows under MinGW
        target_link_options(sprite_editor PRIVATE
                $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-mwindows>
        )
    endif ()

elseif (APPLE OR UNIX) # macOS / Linux
    if (PRODUCTION_BUILD)
        target_link_options(sprite_editor PRIVATE -s)
    endif ()
endif ()

target_compile_definitions(sprite_editor PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties(sprite_editor PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile"
)

target_compile_definitions(sprite_editor PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties(sprite_editor PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile Sprite Editor"
)

# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Src/*.cpp")

target_sources(sprite_editor PRIVATE ${MY_SOURCES})

target_link_libraries(sprite_editor PRIVATE editor_dependency)