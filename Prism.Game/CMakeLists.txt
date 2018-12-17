# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.10)
project(Prism.Game)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
#    add_compile_options(-Wall -Wpedantic)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/../Prism.Engine/lib)

# TODO: Maak dit fatsoenlijk relatief
include_directories(SYSTEM  ${PROJECT_SOURCE_DIR}/../Prism.Engine/lib/include)


file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(Prism.Game ${SRC_FILES})

target_compile_features(Prism.Game PUBLIC cxx_std_17)
target_link_libraries(Prism.Game PRIVATE Prism.Engine)
target_include_directories(Prism.Game PRIVATE src)

set_target_properties(Prism.Game PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        SOVERSION 1)


#add_custom_target(resources ALL
#        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")

add_custom_target(
        Resources
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

#add_custom_command(TARGET Prism.Game POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")