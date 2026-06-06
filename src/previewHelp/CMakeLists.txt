add_library(previewHelp STATIC previewHelp.cpp)
target_include_directories(previewHelp PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(previewHelp)
AddCoverage(previewHelp)
