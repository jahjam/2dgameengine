add_library(APS 
            APS.h 
            Actor.h 
            Actor.cpp 
            Prop.h 
            Prop.tpp
            Script.h
            Script.cpp
            Script.tpp
            Store.h
            Store.tpp
            Director.h
            Director.cpp
            Director.tpp
          )

          target_link_libraries(APS PUBLIC EasyLogging Arena Utils AssetStore)

target_include_directories(APS PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
