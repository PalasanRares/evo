cmake_minimum_required(VERSION 3.13)
project(Evo VERSION 0.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Look for a SDL3 package,
# 2. look for the SDL3-shared component, and
# 3. fail if the shared component cannot be found.
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image-shared)
find_package(SDL3_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL3_ttf-shared)

# Create your game executable target as usual   
add_executable(Evo src/main.cpp)

add_subdirectory(src)
add_subdirectory(include)

# Link to the actual SDL3 library.
target_link_libraries(Evo PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)