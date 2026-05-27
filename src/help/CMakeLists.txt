add_library(assist STATIC help.cpp)
target_include_directories(assist PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(assist)
AddCoverage(assist)
