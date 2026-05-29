add_library(DifferToken STATIC DifferToken.cpp)
target_include_directories(DifferToken PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(DifferToken)
AddCoverage(DifferToken)
