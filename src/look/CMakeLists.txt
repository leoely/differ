add_library(look STATIC look.cpp)
target_include_directories(look PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(look)
AddCoverage(look)
