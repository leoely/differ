add_library(validate STATIC validate.cpp)
target_include_directories(validate PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(validate)
AddCoverage(validate)
