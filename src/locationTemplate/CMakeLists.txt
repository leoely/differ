add_library(locationTemplate STATIC locationTemplate.cpp)
target_include_directories(locationTemplate PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(locationTemplate)
AddCoverage(locationTemplate)
