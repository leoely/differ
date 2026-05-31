add_library(VariableParser STATIC VariableParser.cpp)
target_include_directories(VariableParser PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(VariableParser)
AddCoverage(VariableParser)
