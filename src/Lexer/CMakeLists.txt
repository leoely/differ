add_library(Lexer STATIC Lexer.cpp)
target_include_directories(LocationLexer PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(Lexer)
AddCoverage(Lexer)
