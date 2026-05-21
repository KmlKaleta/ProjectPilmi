cmake_minimum_required(VERSION 3.10)
project(fastNoiseSIMD)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/FastNoiseSIMD/*.cpp"
)

add_library(fastNoiseSIMD)

foreach(SRC IN LISTS MY_SOURCES)
    if (SRC MATCHES "FastNoiseSIMD_avx2.cpp$")
        set(AVX2_SRC ${SRC})
        list(REMOVE_ITEM MY_SOURCES ${SRC})
    endif()
endforeach()

if(MSVC)
    set_source_files_properties(${AVX2_SRC}
        PROPERTIES COMPILE_FLAGS "/arch:AVX2")
else()
    set_source_files_properties(${AVX2_SRC}
        PROPERTIES COMPILE_FLAGS "-mavx2")
endif()

# Add normal sources
target_sources(fastNoiseSIMD PRIVATE ${MY_SOURCES})

# ADD AVX2 SOURCE TOO
target_sources(fastNoiseSIMD PRIVATE ${AVX2_SRC})

target_include_directories(fastNoiseSIMD PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/FastNoiseSIMD"
)