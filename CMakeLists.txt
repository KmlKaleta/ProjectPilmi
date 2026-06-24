cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

#! ! ! ! ! ! !
#set this to ON instead of OFF to ship the game!
#basically this will change the RESOURCES_PATH to be the local path
#! ! ! ! ! ! !
#delete the out folder after changing if visual studio doesn't recognize the change
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
else ()
    add_compile_options(-mavx2 -mfma) # make sure SIMD optimizations take place, but on linux and other platforms
endif ()

project("sheep_goes_devile")

# Add libraries
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(App)


if (PRODUCTION_BUILD)
    # Where the executable should be placed
    set_target_properties(Game PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Game"
    )

    # Where the executable should be placed
    set_target_properties(Editor PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Game"
    )

    # Copy Resources folder after build
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Resources"
            "$<TARGET_FILE_DIR:Game>/Resources"
    )

    # Copy Resources folder after build
    add_custom_command(TARGET Editor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Resources"
            "$<TARGET_FILE_DIR:Editor>/Resources"
    )
endif ()


if (MSVC) # If using the VS compiler...

    target_compile_definitions(engine PUBLIC _CRT_SECURE_NO_WARNINGS)

    if (PRODUCTION_BUILD)
        #YOU CAN REMOVE THE CONSOLE WITH THIS LINE!
        set_target_properties(Game PROPERTIES
                LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" #no console
        )

        set_target_properties(Editor PROPERTIES
                LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" #no console
        )
    endif ()

elseif (MINGW) # Windows / MinGW GCC/Clang
    if (PRODUCTION_BUILD)
        # Remove console on Windows under MinGW
        target_link_options(Game PRIVATE
                $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-mwindows>
        )

        target_link_options(Editor PRIVATE
                $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU>>:-mwindows>
        )
    endif ()

elseif (APPLE OR UNIX) # macOS / Linux
    if (PRODUCTION_BUILD)
        target_link_options(Game PRIVATE -s)
        target_link_options(Editor PRIVATE -s)
    endif ()
endif ()
