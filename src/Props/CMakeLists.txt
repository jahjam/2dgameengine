add_library(Props TransformProp.h)

target_link_libraries(Props PUBLIC EasyLogging)

target_include_directories(Props PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
