cmake_minimum_required(VERSION 3.18)
project(sandbox)

file(GLOB SOURCES "src/**")

if (UNIX)
   file(GLOB DI "dep/DI/lib/*.so*")
endif (UNIX)
if (WIN32)
file(GLOB DI "dep/DI/lib/*.dll*")
endif (WIN32)
set(INCLUDE_DIRECTORIES dep/DI/include dep/DI/include/core dep/DI/include/external)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${DI})
