add_library(DifferLexer STATIC DifferLexer.cpp)
target_include_directories(DifferLexer PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(DifferLexer)
AddCoverage(DifferLexer)
