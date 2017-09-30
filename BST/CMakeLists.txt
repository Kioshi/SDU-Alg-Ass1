cmake_minimum_required (VERSION 2.6)
project (BST)

file(GLOB BST_SOURCES
    "*.h"
    "*.cpp"
)


add_executable(BST ${BST_SOURCES})