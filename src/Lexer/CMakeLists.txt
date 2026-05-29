add_library(Lexer STATIC Lexer.cpp)
target_include_directories(Lexer PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(Lexer)
AddCoverage(Lexer)
