add_library(Game Game.cpp)

target_link_libraries(Game PUBLIC EasyLogging)

target_include_directories(Game PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
