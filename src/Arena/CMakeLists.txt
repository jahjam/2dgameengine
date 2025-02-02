add_library(Arena Arena.h 
                  Arena.tpp 
                  ArenaManager.h 
                  ArenaManager.tpp
                )

target_link_libraries(Arena PUBLIC APS EasyLogging)

target_include_directories(Arena PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
