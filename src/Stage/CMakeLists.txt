add_library(Stage Stage.cpp Stage.h)

target_link_libraries(Stage PUBLIC EasyLogging Arena APS Props Scripts AssetStore)

target_include_directories(Stage PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
