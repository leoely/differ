add_library(generate STATIC generate.cpp)
target_include_directories(generate PUBLIC
  ${TERMCOLOR_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/include"
)
MemoryCheck(generate)
AddCoverage(generate)
