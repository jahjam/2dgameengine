add_library(Scripts MovementScript.h)

target_link_libraries(Scripts PUBLIC EasyLogging APS)

target_include_directories(Scripts PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
