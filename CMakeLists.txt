cmake_minimum_required(VERSION 3.15)
project(2dgameengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable the generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#add_custom_target(link_compile_commands ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#    ${CMAKE_BINARY_DIR}/compile_commands.json
#    ${CMAKE_SOURCE_DIR}/compile_commands.json
#    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
#    COMMENT "Copying compile_commands.json to the project root"
#)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(libs/easyloggingpp)
add_subdirectory(libs/utils)
add_subdirectory(src/Stage)
add_subdirectory(src/AssetStore)
add_subdirectory(src/Scripts)
add_subdirectory(src/Props)
add_subdirectory(src/APS)
add_subdirectory(src/Arena)

add_executable(2dgameengine src/Main.cpp)


# Path to the assets directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# Ensure the assets directory is copied to the build directory
add_custom_command(
    TARGET 2dgameengine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
)

# this sets specific paths where things happen
# 1)  one is where to place the final executable
# 2 ) the second is defining the working directory which
#     will be used when building the project
#     (meaning every path you write will begin
#      from the project root not the relative file)
set_target_properties(2dgameengine PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin  
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}    
)

target_include_directories(2dgameengine PRIVATE 
  EasyLogging 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_MIXER_INCLUDE_DIRS}
  ${glm}
)

target_link_libraries(2dgameengine PRIVATE 
  SDL2
  SDL2_image
  SDL2_ttf
  SDL2_mixer
  glm
  EasyLogging 
  Utils
  Stage
  Scripts
  Props
  APS
  Arena
  AssetStore
)





