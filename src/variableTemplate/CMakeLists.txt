add_library(variableTemplate STATIC variableTemplate.cpp)
target_include_directories(variableTemplate PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(variableTemplate)
AddCoverage(variableTemplate)
