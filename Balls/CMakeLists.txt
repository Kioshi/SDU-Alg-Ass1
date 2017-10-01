cmake_minimum_required (VERSION 2.6)
project (Balls)

file(GLOB BST_SOURCES
    "*.h"
    "*.cpp"
)


add_executable(Balls ${BST_SOURCES})