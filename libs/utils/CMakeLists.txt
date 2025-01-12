add_library(Utils STATIC
  Utils.cpp 
  Utils.h
)

target_include_directories(Utils INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}
)

