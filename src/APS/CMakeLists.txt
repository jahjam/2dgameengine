add_library(APS APS.cpp APS.tpp)

target_link_libraries(APS PUBLIC EasyLogging)

target_include_directories(APS PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
