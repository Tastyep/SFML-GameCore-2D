message(STATUS "[SFML] Resolving external dependency")

# Define SFML version
set(MIN_SFML_VERSION 2.1)

find_package(SFML ${MIN_SFML_VERSION} REQUIRED system window graphics audio)

# Register SFML dependency
list(APPEND EXTERNAL_LIBRARIES ${SFML_LIBRARIES})

message(STATUS "[SFML] Using ${SFML_VERSION}")
