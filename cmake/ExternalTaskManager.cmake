message(STATUS "[TaskManager] Configuring external project")

include(ExternalProject)

set(TASK_MANAGER_DIR ${TASK_MANAGER_DIR})
set(TASK_MANAGER_TARGET task-manager)
set(TASK_MANAGER_ROOT_DIR ${PROJECT_SOURCE_DIR}/${LIB_DIR}/${TASK_MANAGER_DIR})
set(TASK_MANAGER_SOURCE_DIR ${TASK_MANAGER_ROOT_DIR}/src/${TASK_MANAGER_TARGET}/TaskManager)
set(TASK_MANAGER_BINARY_DIR ${TASK_MANAGER_ROOT_DIR}/src/${TASK_MANAGER_TARGET}-build)

# Configure external project
ExternalProject_Add(
  ${TASK_MANAGER_TARGET}
  PREFIX ${TASK_MANAGER_ROOT_DIR}
  GIT_REPOSITORY https://github.com/Tastyep/TaskManager
  GIT_TAG ${TASK_MANAGER_VERSION}
  GIT_PROGRESS 1
  TIMEOUT 60
  SOURCE_DIR ${TASK_MANAGER_SOURCE_DIR}
  BINARY_DIR ${TASK_MANAGER_BINARY_DIR}
  UPDATE_COMMAND ""
  CONFIGURE_COMMAND ${CMAKE_COMMAND}
    "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
    "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
    "-DCMAKE_INSTALL_PREFIX=${TASK_MANAGER_ROOT_DIR}"
    <SOURCE_DIR>
  BUILD_COMMAND $(MAKE)
  INSTALL_COMMAND $(MAKE) install
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)

# Label target as third-party
set_target_properties(${TASK_MANAGER_TARGET} PROPERTIES LABELS TaskManager FOLDER "Third Party")

# Define dependency directories, mimic the needed behavior of find_package
# NOTE: Variable names must respect the conventions of a cmake find-module
set(TASK_MANAGER_INCLUDE_DIRS "${TASK_MANAGER_ROOT_DIR}/include")
list(APPEND TASK_MANAGER_INCLUDE_DIRS "${TASK_MANAGER_ROOT_DIR}/include/TaskManager")
set(TASK_MANAGER_LIBRARY_DIRS ${TASK_MANAGER_ROOT_DIR}/lib)
set(TASK_MANAGER_LIBRARIES ${TASK_MANAGER_LIBRARY_DIRS}/libTaskManager.a)
set(TASK_MANAGER_TARGETS ${TASK_MANAGER_TARGET})

# Add required unix libraries
list(APPEND EXTERNAL_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
