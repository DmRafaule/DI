cmake_minimum_required(VERSION 3.18)
project(sandbox)

file(GLOB SOURCES "src/**")

if (UNIX)
   file(GLOB DI "dep/DI/lib/*.so*")
endif (UNIX)
if (WIN32)
file(GLOB DI "dep/DI/lib/*.dll*")
endif (WIN32)
set(INCLUDE_DIRECTORIES dep/DI/include dep/DI/include/core dep/DI/include/external dep/DI/include/renderer)
set(CMAKE_BUILD_TYPE Debug)
#Move needed resources
file(GLOB RES 
   res
)
file (INSTALL ${RES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file (INSTALL ${RES} DESTINATION ${CMAKE_SOURCE_DIR}/build)# temporary remove and add file independent solver


include_directories(${INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${DI})
