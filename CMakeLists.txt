cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0042 NEW)

set(BIN_NAME "GameCore")
project (${BIN_NAME} CXX)

# Global variables
set(MODULE_DIR cmake)
set(SOURCE_DIR src)
set(INCLUDE_DIR include)
set(LIB_DIR lib)
set(TEST_DIR example)

# CMake properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set(PREDEFINED_TARGETS_FOLDER "CMake")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/${MODULE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

# Resolve dependencies
include(ResolveSFML)
include(ResolveBox2d)


include_directories (${PROJECT_SOURCE_DIR}/${INCLUDE_DIR})
include_directories (${PROJECT_SOURCE_DIR}/${LIB_DIR})

# Local source files
include(Sources)

# Compilation flags
include(Flags)

add_executable(${BIN_NAME} ${SOURCE_FILES})
target_link_libraries(${BIN_NAME} ${EXTERNAL_LIBRARIES})
