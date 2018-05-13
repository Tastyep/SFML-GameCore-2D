message(STATUS "[Hana] Configuring external project")

include(ExternalProject)

set(HANA_DIR ${HANA_DIR})
set(HANA_TARGET hana)
set(HANA_ROOT_DIR ${PROJECT_SOURCE_DIR}/${LIB_DIR}/${HANA_DIR})
set(HANA_SOURCE_DIR ${HANA_ROOT_DIR}/src/${HANA_TARGET}/Hana)

message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

# Configure external project
ExternalProject_Add(
  ${HANA_TARGET}
  PREFIX ${HANA_ROOT_DIR}
  GIT_REPOSITORY https://github.com/boostorg/hana.git
  GIT_TAG ${HANA_VERSION}
  GIT_PROGRESS 1
  TIMEOUT 60
  SOURCE_DIR ${HANA_SOURCE_DIR}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ${CMAKE_COMMAND}
    "-DCMAKE_INSTALL_PREFIX=${HANA_ROOT_DIR}"
    "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
    "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
    <SOURCE_DIR>
  BUILD_COMMAND ${CMAKE_COMMAND} --build . --target install
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
)

# Label target as third-party
set_target_properties(${HANA_TARGET} PROPERTIES LABELS Hana FOLDER "Third Party")

# Define dependency directories, mimic the needed behavior of find_package
# NOTE: Variable names must respect the conventions of a cmake find-module
set(HANA_INCLUDE_DIRS ${HANA_ROOT_DIR}/include)
set(HANA_TARGETS ${HANA_TARGET})
