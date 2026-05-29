add_library(LocationToken STATIC LocationToken.cpp)
target_include_directories(LocationToken PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(LocationToken)
AddCoverage(LocationToken)
