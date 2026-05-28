add_library(LocationLexer STATIC LocationLexer.cpp)
target_include_directories(LocationLexer PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(LocationLexer)
AddCoverage(LocationLexer)
