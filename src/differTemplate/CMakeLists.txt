add_library(differTemplate STATIC differTemalate.cpp)
target_include_directories(differTemplate PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(differTemplate)
AddCoverage(differTempalte)
