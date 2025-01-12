add_library(APS 
            APS.h 
            Actor.h 
            Actor.cpp 
            Prop.h 
            Prop.cpp
            Script.h
            Script.cpp
            Store.h
            Store.cpp
            Director.h
            Director.cpp
          )

          target_link_libraries(APS PUBLIC EasyLogging Arena Utils AssetStore)

target_include_directories(APS PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
