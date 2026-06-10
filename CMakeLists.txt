cmake_minimum_required(VERSION 3.5)
project(argot LANGUAGES C)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "Les builds dans le dossier source sont interdits. Créez un dossier build/.")
endif()

file(GLOB_RECURSE argot_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(argot-obj ${argot_SOURCES})

target_include_directories(argot-obj
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(argot-obj PRIVATE
    -Wall
    -Wextra
    -O3
)

add_library(argot-static STATIC
    $<TARGET_OBJECTS:argot-obj>
)

target_link_libraries(argot-static
    PUBLIC
        argot-obj
)

add_library(argot-shared SHARED
    $<TARGET_OBJECTS:argot-obj>
)

target_link_libraries(argot-shared
    PUBLIC
        argot-obj
)

add_library(argot ALIAS argot-static)

set_target_properties(argot-static PROPERTIES
    OUTPUT_NAME argot
)

set_target_properties(argot-shared PROPERTIES
    OUTPUT_NAME argot
)

set_target_properties(argot-obj PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
