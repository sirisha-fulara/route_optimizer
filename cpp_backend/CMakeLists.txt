cmake_minimum_required(VERSION 3.10)
project(route_optimizer)

# Include the pybind11 and project headers
include_directories(C:/Users/Dell/pybind11/include)
include_directories(${PROJECT_SOURCE_DIR})  # To include graph.h if needed

# Add your source files
set(SOURCES
    route_optimizer.cpp
    graph.cpp
    dijkstra.cpp
)

# Create the Python module as a shared library
add_library(route_optimizer MODULE ${SOURCES})

# Set the output to have a .pyd extension (Windows Python module)
set_target_properties(route_optimizer PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
)

# Find Python (required for pybind11 to work)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Link Python include and lib dirs
target_include_directories(route_optimizer PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(route_optimizer PRIVATE ${Python3_LIBRARIES})
