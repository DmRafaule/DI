
cmake_minimum_required(VERSION 3.18)
project(DI)



file(GLOB SOURCES "src/*.cpp" "src/core/*.cpp" "dep/IMGUI/*.cpp" "dep/IMGUI/backends/*.cpp")


if (WIN32)
   file(GLOB SDL2 "dep/SDL2/build/*.dll*")
   file(GLOB GLEW "dep/GLEW/lib/*.dll*")
   file(GLOB SPDLOG "dep/SPDLOG/build/*.dll*")
endif (WIN32)
if (UNIX)
   file(GLOB SDL2 "dep/SDL2/build/*.so*")
   file(GLOB GLEW "dep/GLEW/lib/*.so*")
   file(GLOB SPDLOG "dep/SPDLOG/build/*.so*")
endif(UNIX)
set(GL -lGL -lglut )
set(INCLUDE_DIRECTORIES 
   dep/SDL2/include 
   dep/GLEW/include 
   dep/STB/include 
   dep/GLM 
   src/core 
   src/events 
   dep/SPDLOG/include 
   dep/IMGUI
   dep/IMGUI/backends)
set(CMAKE_CXX_FLAGS -pthread)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_BUILD_TYPE Debug)


include_directories(${INCLUDE_DIRECTORIES})
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2} ${SDL2_image} ${GLEW} ${GL} ${SPDLOG})