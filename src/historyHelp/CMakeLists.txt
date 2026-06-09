add_library(historyHelp STATIC historyHelp.cpp)
target_include_directories(historyHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(historyHelp)
AddCoverage(historyHelp)
