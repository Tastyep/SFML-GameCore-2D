# Copyright (C) 2015 Etix Labs - All Rights Reserved.
# All information contained herein is, and remains the property of Etix Labs and its suppliers,
# if any. The intellectual and technical concepts contained herein are proprietary to Etix Labs
# Dissemination of this information or reproduction of this material is strictly forbidden unless
# prior written permission is obtained from Etix Labs.

message(STATUS "[Box2d] Resolving external dependency")

# Define Box2d version
set(BOX2D_VERSION 2.3.0)
set(BOX2D_DIR Box2D)

# Register Box2d dependency
file(GLOB_RECURSE BOX2D_SOURCE_FILES "${PROJECT_SOURCE_DIR}/${LIB_DIR}/${BOX2D_DIR}/*pp")
list(APPEND SOURCE_FILES ${BOX2D_SOURCE_FILES})

message(STATUS "[Box2d] Using ${BOX2D_VERSION}")
