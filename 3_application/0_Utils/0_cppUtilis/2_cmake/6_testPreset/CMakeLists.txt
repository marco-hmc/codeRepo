cmake_minimum_required(VERSION 3.12...3.24)

project(testbed
        VERSION 1.0
        DESCRIPTION "My testbed project for cpp features"
        LANGUAGES CXX)

# Assure that we're not building in source
include(cmake/PreventInSourceBuilds.cmake)

add_executable(myproject)
target_sources(myproject PRIVATE src/main.cpp)

# Apply Preset settings to project
include(${CMAKE_SOURCE_DIR}/cmake/ApplyPreset.cmake)
apply_preset_to(myproject)

