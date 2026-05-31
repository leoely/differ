add_library(VariableLexer STATIC VariableLexer.cpp)
target_include_directories(VariableLexer PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(VariableLexer)
AddCoverage(VariableLexer)
