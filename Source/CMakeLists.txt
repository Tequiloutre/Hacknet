cmake_minimum_required(VERSION 3.5)

# Project name
set(PROJECT_NAME Hacknet)
project (${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../${PROJECT_NAME})

# Include external libraries
add_subdirectory(External)

include_directories(
    External/json/include
)

# Project files
file(GLOB_RECURSE SRCS ${PROJECT_NAME}/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_NAME}/*.h ${PROJECT_NAME}/*.hpp ${PROJECT_NAME}/*.inl)

set(PROJECT_SOURCES
    ${PROJECT_NAME}.cpp
    ${SRCS}
    ${HEADERS}
)

# Project
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/)
