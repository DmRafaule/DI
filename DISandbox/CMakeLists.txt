cmake_minimum_required(VERSION 3.18)
project(sandbox)

file(GLOB SOURCES "src/**")

file(GLOB DI "dep/DI/lib/*.a*")
set(INCLUDE_DIRECTORIES dep/DI/include dep/DI/include/core)
set(CMAKE_BUILD_TYPE Release)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${DI})
