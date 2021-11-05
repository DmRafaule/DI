
cmake_minimum_required(VERSION 3.18)
project(DI)

file(GLOB SOURCES "src/*.cpp" "src/core/*.cpp")

file(GLOB SDL2 "dep/SDL2/lib/*.so*")
file(GLOB GLEW "dep/GLEW/lib/*.so*")
file(GLOB SPDLOG "dep/SPDLOG/build/*.a*")
set(GL -lGL -lglut )
set(INCLUDE_DIRECTORIES dep/SDL2/include dep/GLEW/include dep/STB/include dep/GLM src/core dep/SPDLOG/include)
set(CMAKE_CXX_FLAGS -pthread)



include_directories(${INCLUDE_DIRECTORIES})
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2} ${SDL2_image} ${GLEW} ${GL} ${SPDLOG})