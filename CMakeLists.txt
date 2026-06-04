cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

#! ! ! ! ! ! !
#set this to ON instead of OFF to ship the game!
#basically this will change the RESOURCES_PATH to be the local path
#! ! ! ! ! ! !
#delete the out folder after changing if visual studio doesn't recognize the change
set(PRODUCTION_BUILD OFF CACHE BOOL "Production build" FORCE)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
else ()
    add_compile_options(-mavx2 -mfma) # make sure SIMD optimizations take place, but on linux and other platforms
endif ()


# Ensure raylib is build as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static libraries" FORCE)

project("sheep_goes_devile")

# Add libraries
add_subdirectory(ThirdParty/raylib-6.0)
add_subdirectory(ThirdParty/imgui-docking)
add_subdirectory(ThirdParty/rlimgui)
add_subdirectory(ThirdParty/json-3.12.0)
add_subdirectory(ThirdParty/raygui-4.0)

# MY_SOURCES is defined to be a list of all the source files for my game 
# DON'T ADD THE SOURCES BY HAND, they are already added with this macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}" app.rc)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PRIVATE
        $<$<CONFIG:Release>:PRODUCTION_BUILD=1>
        $<$<NOT:$<CONFIG:Release>>:PRODUCTION_BUILD=0>
)

set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
        OUTPUT_NAME "Sheep Goes Devile"
)

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

if (PRODUCTION_BUILD)
    # Where the executable should be placed
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Game"
    )

    # Copy Resources folder after build
    add_custom_command(TARGET "${CMAKE_PROJECT_NAME}" POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Resources"
            "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Resources"
    )
endif ()


if (PRODUCTION_BUILD)
    # setup the ASSETS_PATH macro to be in the root folder of your exe
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./Resources/")

    # remove the option to debug asserts.
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)

else ()
    # This is useful to get an ASSETS_PATH in your IDE during development
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

endif ()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})


if (MSVC) # If using the VS compiler...

    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

    if (PRODUCTION_BUILD)
        #YOU CAN REMOVE THE CONSOLE WITH THIS LINE!
        set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
    endif ()

elseif (MINGW) # Windows / MinGW GCC/Clang
    if (PRODUCTION_BUILD)
        # Remove console on Windows under MinGW
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE
                -mwindows
        )
    endif ()

elseif (APPLE OR UNIX) # macOS / Linux
    if (PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
    endif ()
endif ()


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src/Platform")

# Link to libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui nlohmann_json raygui)
