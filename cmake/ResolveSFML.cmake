# Copyright (C) 2015 Etix Labs - All Rights Reserved.
# All information contained herein is, and remains the property of Etix Labs and its suppliers,
# if any. The intellectual and technical concepts contained herein are proprietary to Etix Labs
# Dissemination of this information or reproduction of this material is strictly forbidden unless
# prior written permission is obtained from Etix Labs.

message(STATUS "[SFML] Resolving external dependency")

# Define SFML version
set(MIN_SFML_VERSION 2.1)

find_package(SFML ${MIN_SFML_VERSION} REQUIRED system window graphics audio)

# Register SFML dependency
list(APPEND EXTERNAL_LIBRARIES ${SFML_LIBRARIES})

message(STATUS "[SFML] Using ${SFML_VERSION}")
