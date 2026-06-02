add_library(validateHelp STATIC validateHelp.cpp)
target_include_directories(validateHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(validateHelp)
AddCoverage(validateHelp)
