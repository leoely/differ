add_library(clear STATIC clear.cpp)
target_include_directories(clear PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(clear)
AddCoverage(clear)
