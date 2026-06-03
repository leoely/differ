add_library(generateHelp STATIC generateHelp.cpp)
target_include_directories(generateHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(generateHelp)
AddCoverage(generateHelp)
