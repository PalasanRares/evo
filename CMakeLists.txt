cmake_minimum_required(VERSION 3.16)
project(Evo VERSION 0.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDLTTF_VENDORED ON)

add_subdirectory(dependencies/SDL EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(dependencies/SDL_ttf EXCLUDE_FROM_ALL)

# Create your game executable target as usual   
add_executable(Evo src/main.cpp)

add_subdirectory(src)
add_subdirectory(include)

# Link to the actual SDL3 library.
target_link_libraries(Evo PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

add_custom_command(TARGET Evo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/res"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res"
    COMMENT "Copying resources"
)
