add_library(locationTemplate STATIC locationTemplate.cpp)
target_include_directories(LocationParser PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  ${TERMCOLOR_INCLUDE_DIRS}
)
MemoryCheck(locationTemplate)
AddCoverage(locationTempalte)
