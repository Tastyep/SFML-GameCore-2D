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
set(CMAKE_BUILD_TYPE ${BUILD_TYPE})


message(STATUS "Building ${BUILD_TYPE} ${PROJECT_NAME}\n----------------------------")
message(STATUS "[Compiler] Using ${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")

# Attempt to find threads library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Resolve dependencies
include(ResolveSFML)
include(ResolvePlayRho)
include(ResolveHana)
include(ResolveHitboxBuilder)
include(ResolveTaskManager)

# Third party include directories
include_directories(SYSTEM ${EXTERNAL_INCLUDE_DIRS})

# Third party link directories
link_directories(${EXTERNAL_LIBRARY_DIRS})

# Local include directories
include_directories (${PROJECT_SOURCE_DIR}/${INCLUDE_DIR})

# Local source files
include(Sources)

# Compilation flags
include(Flags)

if(GAME_CORE_ENABLE_CLANGTIDY AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  include(EnableClangTidy)
  enable_clangtidy(SOURCES "${SOURCE_FILES}")
endif()

add_executable(${BIN_NAME} ${SOURCE_FILES})

add_dependencies(${BIN_NAME} ${EXTERNAL_DEPENDENCIES})

target_link_libraries(${BIN_NAME} ${EXTERNAL_LIBRARIES})
