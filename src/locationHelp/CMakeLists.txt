add_library(locationHelp STATIC locationHelp.cpp)
target_include_directories(locationHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(locationHelp)
AddCoverage(locationHelp)
