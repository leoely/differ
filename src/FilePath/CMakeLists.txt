add_library(FilePath STATIC FilePath.cpp)
target_include_directories(FilePath PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(FilePath)
AddCoverage(FilePath)
