
cmake_minimum_required(VERSION 3.18)
project(DI)



file(GLOB SOURCES_LIBS 
   "dep/include/core/*.cpp" 
   "dep/include/renderer/*.cpp"
   "dep/include/external/imgui/*.cpp" 
   "dep/include/external/imgui/backends/*.cpp")
file(GLOB SOURCES_APP
   "src/*.cpp"
)

# Here maybe other directory
if (WIN32)
   file(GLOB LIBS "dep/lib/*.dll*")
   file(GLOB DI "build/*.dll*")
endif (WIN32)
if (UNIX)
   file(GLOB LIBS "dep/lib/*.so*")
   file(GLOB DI "build/*.so*")
endif(UNIX)

set(GL -lGL -lglut )
set(INCLUDE_DIRECTORIES 
   dep/include 
   dep/include/core
   dep/include/external
   dep/include/external/imgui
   dep/include/external/imgui/backends
   dep/include/renderer
   )
set(CMAKE_CXX_FLAGS -pthread )
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_TYPE Debug)

#Move needed resources
file(GLOB RES 
   res
)
file (INSTALL ${RES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

include_directories(${INCLUDE_DIRECTORIES})
add_library(${PROJECT_NAME} ${SOURCES_LIBS})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${GL})
add_executable(sandbox ${SOURCES_APP})
target_link_libraries(sandbox ${DI})