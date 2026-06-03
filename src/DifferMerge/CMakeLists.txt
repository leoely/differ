add_library(DifferMerge STATIC DifferMerge.cpp)
target_include_directories(DifferMerge PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(DifferMerge)
AddCoverage(DifferMerge)
