add_library(Arena Arena.h 
                  Arena.cpp 
                  ArenaManager.h 
                  ArenaManager.cpp
                )

target_link_libraries(Arena PUBLIC APS EasyLogging)

target_include_directories(Arena PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
