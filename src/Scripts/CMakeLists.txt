add_library(Scripts MovementScript.h RenderScript.h)

target_link_libraries(Scripts PUBLIC EasyLogging APS AssetStore)

target_include_directories(Scripts PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
