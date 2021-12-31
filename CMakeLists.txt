
cmake_minimum_required(VERSION 3.18)
project(DI)
set (DIEditor DIEditor)

file(GLOB RES 
   res
)
file(GLOB SOURCES 
   "src/*.cpp" 
   "src/core/*.cpp" 
   "src/renderer/*.cpp"
   "dep/IMGUI/*.cpp" 
   "dep/IMGUI/backends/*sdl*.cpp" 
   "dep/IMGUI/backends/*opengl*.cpp")
file(GLOB SOURCES_EDITOR
   "src/editor/*.cpp"
)


if (WIN32)
   file(GLOB SDL2 "dep/SDL2/build/*.dll*")
   file(GLOB GLEW "dep/GLEW/lib/*.dll*")
   file(GLOB SPDLOG "dep/SPDLOG/build/*.dll*")
   file(GLOB ASSIMP "dep/ASSIMP/build/bin/*.dll*")
endif (WIN32)
if (UNIX)
   file(GLOB SDL2 "dep/SDL2/build/*.so*")
   file(GLOB GLEW "dep/GLEW/lib/*.so*")
   file(GLOB SPDLOG "dep/SPDLOG/build/*.so*")
   file(GLOB ASSIMP "dep/ASSIMP/build/bin/*.so*")
endif(UNIX)
set(GL -lGL -lglut )
set(INCLUDE_DIRECTORIES 
   dep/SDL2/include 
   dep/GLEW/include 
   dep/STB/include 
   dep/GLM 
   src
   src/editor
   src/core 
   src/renderer
   dep/SPDLOG/include 
   dep/IMGUI
   dep/IMGUI/backends
   dep/ASSIMP/include
   dep/ASSIMP/build/include
   )
set(CMAKE_CXX_FLAGS -pthread)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_TYPE Debug)


include_directories(${INCLUDE_DIRECTORIES})
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2} ${SDL2_image} ${GLEW} ${GL} ${SPDLOG} ${ASSIMP})

if (WIN32)
   file(GLOB DI_LIB "lib/*.dll*")
endif (WIN32)
if (UNIX)
   file(GLOB DI_LIB "lib/*.so*")
endif(UNIX)

add_executable(${DIEditor} ${SOURCES} ${SOURCES_EDITOR})
target_link_libraries(${DIEditor} ${PROJECT_NAME} ${CMAKE_DL_LIBS})

file (INSTALL ${CMAKE_SOURCE_DIR}/lib/${DIEditor} DESTINATION ${CMAKE_SOURCE_DIR}/bin)# make check if file exist
file (INSTALL ${RES} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
file (INSTALL ${DI_LIB} DESTINATION ${CMAKE_SOURCE_DIR}/bin)




