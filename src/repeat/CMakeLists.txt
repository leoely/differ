add_library(repeat STATIC repeat.cpp)
target_include_directories(repeat PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(repeat)
AddCoverage(repeat)
