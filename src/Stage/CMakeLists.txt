add_library(Stage Stage.cpp)

target_link_libraries(Stage PUBLIC EasyLogging)

target_include_directories(Stage PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
