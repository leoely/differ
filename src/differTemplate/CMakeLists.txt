add_library(differTemplate STATIC differTemplate.cpp)
target_include_directories(differTemplate PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(differTemplate)
AddCoverage(differTemplate)
