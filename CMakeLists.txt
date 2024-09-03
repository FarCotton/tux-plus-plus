# Minimum CMake version required, we'll just use the latest version.
cmake_minimum_required(VERSION 3.22)
# Project name, version and description
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set debug and optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra -Wpedantic")

# Create an executable
add_executable(${PROJECT_NAME} "src/main.cpp")

# Find our pre-installed DPP package (using FindDPP.cmake).
find_package(DPP REQUIRED)

# Link the pre-installed DPP package to the main executable
target_link_libraries(${PROJECT_NAME} ${DPP_LIBRARIES})

# Include the DPP directories for the main executable
target_include_directories(${PROJECT_NAME} PRIVATE ${DPP_INCLUDE_DIR})

# Set C++ version for the main executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Collect all .cpp files in the src/cogs directory
file(GLOB_RECURSE COG_SOURCES "src/cogs/*/*.cpp")

# Iterate over each cog source file
foreach(COG_SOURCE ${COG_SOURCES})

  # Extract the cog name (first wildcard) from the file path
  get_filename_component(COG_NAME ${COG_SOURCE} DIRECTORY)
  get_filename_component(COG_NAME ${COG_NAME} NAME)

  # Create a shared library for the cog
  add_library(${COG_NAME} SHARED ${COG_SOURCE})

  # Link the DPP libraries to the cog library
  target_link_libraries(${COG_NAME} ${DPP_LIBRARIES})

  # Include the DPP directories for the cog library
  target_include_directories(${COG_NAME} PRIVATE ${DPP_INCLUDE_DIR})

  # Set the output directory for the cog library to ./build/cogs/<cog_name>
  set_target_properties(${COG_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/cogs/${COG_NAME}"
  )

  # Set C++ version for the cog library
  set_target_properties(${COG_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
  )
endforeach()