# Author: Vincent Brouwers <vpe.brouwers@avans.nl>
cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.1.3)
project(Prism.Engine
        VERSION 0.0.1
        DESCRIPTION "A simple library for use within the AI course at Avans University"
        LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/W3)

    if (NOT DEFINED SDL2_DIR)
        set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2")
    endif ()
    if (NOT DEFINED SDL2_IMAGE_DIR)
        set(SDL2_IMAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2_image")
    endif (NOT DEFINED SDL2_IMAGE_DIR)


    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
else () # Assume GCC/Clang on a Unix os
    include(FindPkgConfig)
    find_package(SDL2 REQUIRED)
    #    find_package(SDL2_image REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    find_package(OpenGL REQUIRED)
    find_package(FMT REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(Assimp REQUIRED)
    find_package(Freetype REQUIRED)

    #    link_libraries(libc++fs)

    #    add_compile_options(-Wall -Wpedantic -Werror)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/lib/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_library(Prism.Engine SHARED ${SRC_FILES})

#target_compile_features(Prism.Engine PUBLIC cxx_std_17)
if (MSVC)
    set_target_properties(Prism.Engine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif ()
set_target_properties(Prism.Engine PROPERTIES
        VERSION ${PROJECT_VERSION}
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        SOVERSION 1)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(FILESYSTEM_LIB c++experimental)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(FILESYSTEM_LIB stdc++fs)
endif ()

#target_link_libraries(Prism.Engine PRIVATE ${ASSIMP_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Prism.Engine PRIVATE
        ${ASSIMP_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${FILESYSTEM_LIB}
        )

target_include_directories(Prism.Engine PUBLIC include)
target_include_directories(Prism.Engine PRIVATE
        src
        ${ASSIMP_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${FMT_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
        )


# find_package(GTest)
# if(GTest_FOUND)
#     enable_testing()
#     add_executable(kmint_tests
#                    test/util/wrapped_iterator.cpp
#                    test/graph/graph.cpp
#                    test/math/size.cpp
#                    test/map/map.cpp
#                    test/play/stage.cpp
#                    test/ui/events/modifier.cpp
#     )
#     target_compile_features(kmint_tests PUBLIC cxx_std_17)
#     target_include_directories(kmint_tests PUBLIC include)
#     target_link_libraries(kmint_tests kmint GTest::GTest GTest::Main)
#     add_test(AllTests kmint_tests)
# endif()

install(DIRECTORY include/
        DESTINATION include/
        FILES_MATCHING PATTERN "*.h")
install(TARGETS Prism.Engine
        DESTINATION lib)
