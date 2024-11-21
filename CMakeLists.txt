cmake_minimum_required(VERSION 3.10)
project(SuperSearch)

# Set C++ standard back to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find all source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(supersearch ${SOURCES})

# Add RapidJSON
include_directories(${PROJECT_SOURCE_DIR}/external/rapidjson/include)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 