add_library(LocationLexer STATIC LocationLexer.cpp)
target_include_directories(LocationParser PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(LocationLexer)
AddCoverage(LocationLexer)
