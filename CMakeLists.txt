
cmake_minimum_required(VERSION 3.18)
project(DI)


file(GLOB SOURCES_LIBS 
   "dep/DI/core/*.cpp" 
   "dep/DI/renderer/*.cpp"
   "dep/IMGUI/imgui/*.cpp" 
   "dep/IMGUI/imgui/backends/*.cpp")
file(GLOB SOURCES_APP
   "src/*.cpp"
)

# Here maybe other directory
if (WIN32)
   file(GLOB LIBS 
               "dep/ASSIMP/lib/*.dll*" 
               "dep/GLEW/lib/*.dll*" 
               "dep/SDL2/lib/*.dll*")
   file(GLOB DI "build/*.dll*")
endif (WIN32)
if (UNIX)
file(GLOB LIBS 
               "dep/ASSIMP/lib/*.so*" 
               "dep/GLEW/lib/*.so*" 
               "dep/SDL2/lib/*.so*")
   file(GLOB DI "build/*.so*")
endif(UNIX)

set(GL -lGL -lglut )
set(INCLUDE_DIRECTORIES 
   dep/DI 
   dep/DI/core
   dep/DI/renderer
   dep/ASSIMP/include
   dep/GLEW/include
   dep/GLM
   dep/SDL2/include
   dep/SPDLOG
   dep/STB
   dep/IMGUI/imgui
   dep/IMGUI/imgui/backends
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