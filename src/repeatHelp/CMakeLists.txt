add_library(repeatHelp STATIC repeatHelp.cpp)
target_include_directories(repeatHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(repeatHelp)
AddCoverage(repeatHelp)
