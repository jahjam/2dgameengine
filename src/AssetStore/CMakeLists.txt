add_library(AssetStore AssetStore.h AssetStore.cpp)

target_link_libraries(AssetStore PUBLIC EasyLogging)

target_include_directories(AssetStore PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
