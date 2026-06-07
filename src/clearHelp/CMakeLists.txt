add_library(clearHelp STATIC clearHelp.cpp)
target_include_directories(clearHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(clearHelp)
AddCoverage(clearHelp)
