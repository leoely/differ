add_library(VariableMerge STATIC VariableMerge.cpp)
target_include_directories(VariableMerge PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(VariableMerge)
AddCoverage(VariableMerge)
