cmake_minimum_required(VERSION 3.18)
project(GameEngine)

# Create Engine libs
add_subdirectory(${CMAKE_SOURCE_DIR}/DI ${CMAKE_SOURCE_DIR}/DI/bin)
# Move needed files
file(GLOB LIBS ${CMAKE_SOURCE_DIR}/DI/bin/*.a)
file(GLOB INCLUDE ${CMAKE_SOURCE_DIR}/DI/src/*.hpp)

file(INSTALL ${LIBS} DESTINATION ${CMAKE_SOURCE_DIR}/DISandbox/dep/DI/lib)
file(INSTALL ${INCLUDE} DESTINATION ${CMAKE_SOURCE_DIR}/DISandbox/dep/DI/include)

# Create actual app
add_subdirectory(${CMAKE_SOURCE_DIR}/DISandbox ${CMAKE_SOURCE_DIR}/DISandbox/build)