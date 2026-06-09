add_library(question STATIC question.cpp)
target_include_directories(question PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(question)
AddCoverage(question)
