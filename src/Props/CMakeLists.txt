add_library(Props TransformProp.h RigidBodyProp.h SpriteProp.h)

target_link_libraries(Props PUBLIC EasyLogging APS)

target_include_directories(Props PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
