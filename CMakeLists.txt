# Author: Vincent Brouwers <vpe.brouwers@avans.nl>
cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This ensures both SDL2 and SDL2_image are known in both projects.
# Although kmintapp can be built without these two packages being found,
# it helps with gathering all variables required for a runnable kmintapp
if (MSVC)
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2")
    set(SDL2_IMAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2_image")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
endif (MSVC)

# Ensure all build projects arrive in the same directory
set(INSTALL_DIR ${PROJECT_BINARY_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${INSTALL_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${INSTALL_DIR})

add_subdirectory(Prism.Engine)
add_subdirectory(Prism.Game)
if (MSVC)
    list(GET SDL2_LIBRARIES 0 HEAD_SDL2_LIBRARIES)
    get_filename_component(SDL2_DLL_DIR ${HEAD_SDL2_LIBRARIES} DIRECTORY CACHE)
    list(GET SDL2_IMAGE_LIBRARIES 0 HEAD_SDL2_IMAGE_LIBRARIES)
    get_filename_component(SDL2_IMAGE_DLL_DIR ${HEAD_SDL2_IMAGE_LIBRARIES} DIRECTORY CACHE)
    file(GLOB SDL2_DLLS "${SDL2_DLL_DIR}/*.dll")
    file(GLOB SDL2_IMAGE_DLLS "${SDL2_IMAGE_DLL_DIR}/*.dll")


    add_custom_target(dependencies ALL
            #SOURCES kmintapp/resources/cow.png kmintapp/resources/rabbit.png kmintapp/resources/map3.png
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DLLS} ${SDL2_IMAGE_DLLS} ${INSTALL_DIR})
endif (MSVC)

file(GLOB_RECURSE ALL_SOURCE_FILES Prism.*/src/**.cpp Prism.*/include/**.h)

add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        clang-tidy
        COMMAND /usr/bin/clang-tidy
        ${ALL_SOURCE_FILES}
        -config=''
        -fix
        --
        -std=c++17
        ${INCLUDE_DIRECTORIES}
)
