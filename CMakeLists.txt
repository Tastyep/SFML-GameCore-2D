cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0042 NEW)

set(NAME "GameCore")
project (${NAME} CXX)

# Global variables
set(MODULE_DIR cmake/Modules)
set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(TEST_DIR example)

# CMake properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set(PREDEFINED_TARGETS_FOLDER "CMake")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/${MODULE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find packages
find_package(SFML 2.1 REQUIRED system window graphics audio)

# Build variables
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

include_directories (${PROJECT_SOURCE_DIR}/${INCLUDE_DIR})

# Source files
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/${SOURCE_DIR}/*pp")
file(GLOB_RECURSE TEST_FILES "${PROJECT_SOURCE_DIR}/${TEST_DIR}/*pp")
list(APPEND SOURCE_FILES ${TEST_FILES})

add_executable(${NAME} ${SOURCE_FILES})

target_link_libraries (${NAME} ${SFML_LIBRARIES})
