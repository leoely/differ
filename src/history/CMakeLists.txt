add_library(history STATIC history.cpp)
target_include_directories(history PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(history)
AddCoverage(history)
