add_library(LocationMerge STATIC LocationMerge.cpp)
target_include_directories(LocationMerge PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(LocationMerge)
AddCoverage(LocationMerge)
