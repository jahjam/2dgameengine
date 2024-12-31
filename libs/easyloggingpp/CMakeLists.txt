add_library(EasyLogging STATIC
  easylogging++.cc
  easylogging++.h
)

target_include_directories(EasyLogging INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}
)

