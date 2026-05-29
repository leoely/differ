add_library(differTemplate STATIC differTemplate.cpp)
target_include_directories(differTemplate PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(differTemplate)
AddCoverage(differTemplate)
