##################################
#########autogenerate#############

cmake_minimum_required(VERSION 3.10)
project(SusHeld)

set(CMAKE_CXX_STANDARD 20)

# Add include directories
# include_directories(include)

# Add source files 
file(GLOB SOURCES "src/*.cpp")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Create the executable
add_executable(SusHeld ${SOURCES})

# Link the libraries
target_link_libraries(SusHeld SDL2::SDL2 SDL2_image::SDL2_image)

# Copy logo.png
file(COPY ${CMAKE_SOURCE_DIR}/logo.png DESTINATION ${CMAKE_BINARY_DIR})
