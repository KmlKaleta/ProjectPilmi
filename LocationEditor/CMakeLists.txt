cmake_minimum_required(VERSION 3.16)

project(location_editor)

add_executable(location_editor app.rc)

set_property(TARGET location_editor PROPERTY CXX_STANDARD 17)

if (MSVC)
    target_compile_options(location_editor PRIVATE /utf-8)
else()
    target_compile_options(location_editor PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
else ()
    add_compile_options(-mavx2 -mfma) # make sure SIMD optimizations take place, but on linux and other platforms
endif ()

target_compile_definitions(location_editor PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties(location_editor PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile Location Editor"
)

if (MSVC) # If using the VS compiler...

    target_compile_definitions(location_editor PUBLIC _CRT_SECURE_NO_WARNINGS)

    if (PRODUCTION_BUILD)
        #YOU CAN REMOVE THE CONSOLE WITH THIS LINE!
        set_target_properties(location_editor PROPERTIES
                LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" #no console
        )
    endif ()

elseif (MINGW) # Windows / MinGW GCC/Clang
    if (PRODUCTION_BUILD)
        # Remove console on Windows under MinGW
        target_link_options(location_editor PRIVATE
                $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-mwindows>
        )
    endif ()

elseif (APPLE OR UNIX) # macOS / Linux
    if (PRODUCTION_BUILD)
        target_link_options(location_editor PRIVATE -s)
    endif ()
endif ()

# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Src/*.cpp")

target_sources(location_editor PRIVATE ${MY_SOURCES})

target_link_libraries(location_editor PRIVATE editor_dependency)