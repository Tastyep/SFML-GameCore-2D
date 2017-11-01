message(STATUS "[Hana] Resolving external dependency")

set(HANA_DIR Hana)

include(ExternalHana)

list(APPEND EXTERNAL_DEPENDENCIES ${HANA_TARGETS})
list(APPEND EXTERNAL_INCLUDE_DIRS ${HANA_INCLUDE_DIRS})

message(STATUS "[Hana] Using ${HANA_VERSION}")
