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
add_subdirectory(App)
add_subdirectory(EditorDependency)
add_subdirectory(Editor)
add_subdirectory(SpriteEditor)

