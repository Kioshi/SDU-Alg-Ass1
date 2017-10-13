cmake_minimum_required (VERSION 2.6)
SET(PROJECT_NAME Balls)
project (${PROJECT_NAME})

file(GLOB BST_SOURCES
    "*.h"
    "*.cpp"
)


add_executable(Balls ${BST_SOURCES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})