cmake_minimum_required(VERSION 3.18)
project(GameEngine)


add_subdirectory( ${CMAKE_SOURCE_DIR}/DI/dep/SDL2 ${CMAKE_SOURCE_DIR}/DI/dep/SDL2/build )
add_subdirectory( ${CMAKE_SOURCE_DIR}/DI/dep/GLEW ${CMAKE_SOURCE_DIR}/DI/dep/GLEW )
add_subdirectory( ${CMAKE_SOURCE_DIR}/DI/dep/SPDLOG ${CMAKE_SOURCE_DIR}/DI/dep/SPDLOG/build )

# Create Engine libs
add_subdirectory(${CMAKE_SOURCE_DIR}/DI ${CMAKE_SOURCE_DIR}/DI/lib)
# Move needed files
file(GLOB LIBS ${CMAKE_SOURCE_DIR}/DI/lib/lib*.[a,so,dll,lib]*) # Add all neede submodules in project
file(
   GLOB 
      INCLUDE_EXTERNAL 
         ${CMAKE_SOURCE_DIR}/DI/dep/GLEW/include/* 
         ${CMAKE_SOURCE_DIR}/DI/dep/GLM/glm
         ${CMAKE_SOURCE_DIR}/DI/dep/SDL2/include/*
         ${CMAKE_SOURCE_DIR}/DI/dep/SPDLOG/include/*
         ${CMAKE_SOURCE_DIR}/DI/dep/STB/include/*
)
file(
   GLOB 
      INCLUDE_INTERNAL 
         ${CMAKE_SOURCE_DIR}/DI/src/** 
)

file(INSTALL ${LIBS} DESTINATION ${CMAKE_SOURCE_DIR}/DISandbox/dep/DI/lib)
file(INSTALL ${INCLUDE_EXTERNAL} DESTINATION ${CMAKE_SOURCE_DIR}/DISandbox/dep/DI/include/external)
file(INSTALL ${INCLUDE_INTERNAL} DESTINATION ${CMAKE_SOURCE_DIR}/DISandbox/dep/DI/include)

# Create actual app
add_subdirectory(${CMAKE_SOURCE_DIR}/DISandbox ${CMAKE_SOURCE_DIR}/DISandbox/build)