add_library(location STATIC location.cpp)
target_include_directories(location PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(location)
AddCoverage(location)
