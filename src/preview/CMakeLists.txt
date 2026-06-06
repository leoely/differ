add_library(preview STATIC preview.cpp)
target_include_directories(preview PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(preview)
AddCoverage(preview)
