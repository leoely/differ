add_library(lookHelp STATIC lookHelp.cpp)
target_include_directories(lookHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(lookHelp)
AddCoverage(lookHelp)
