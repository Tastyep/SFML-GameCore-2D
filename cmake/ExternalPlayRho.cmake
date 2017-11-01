message(STATUS "[PlayRho] Configuring external project")

include(ExternalProject)

set(PLAYRHO_DIR ${PLAYRHO_DIR})
set(PLAYRHO_TARGET playrho)
set(PLAYRHO_ROOT_DIR ${PROJECT_SOURCE_DIR}/${LIB_DIR}/${PLAYRHO_DIR})
set(PLAYRHO_SOURCE_DIR ${PLAYRHO_ROOT_DIR}/src/${PLAYRHO_TARGET}/PlayRho)
set(PLAYRHO_BINARY_DIR ${PLAYRHO_ROOT_DIR}/src/${PLAYRHO_TARGET}-build)

# Configure external project
ExternalProject_Add(
  ${PLAYRHO_TARGET}
  PREFIX ${PLAYRHO_ROOT_DIR}
  GIT_REPOSITORY https://github.com/louis-langholtz/PlayRho
  GIT_TAG master
  GIT_PROGRESS 1
  TIMEOUT 60
  SOURCE_DIR ${PLAYRHO_SOURCE_DIR}
  BINARY_DIR ${PLAYRHO_BINARY_DIR}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ${CMAKE_COMMAND}
    "-DPLAYRHO_BUILD_SHARED=ON"
    "-DPLAYRHO_INSTALL=ON"
    "-DCMAKE_INSTALL_PREFIX=${PLAYRHO_ROOT_DIR}"
    <SOURCE_DIR>
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND $(MAKE) install
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)

# Label target as third-party
set_target_properties(${PLAYRHO_TARGET} PROPERTIES LABELS PlayRho FOLDER "Third Party")

# Define dependency directories, mimic the needed behavior of find_package
# NOTE: Variable names must respect the conventions of a cmake find-module
set(PLAYRHO_INCLUDE_DIRS ${PLAYRHO_ROOT_DIR}/include)
set(PLAYRHO_LIBRARY_DIRS ${PLAYRHO_ROOT_DIR}/lib)
set(PLAYRHO_LIBRARIES ${PLAYRHO_LIBRARY_DIRS}/libPlayRho.so)
set(PLAYRHO_TARGETS ${PLAYRHO_TARGET})
