add_executable(DifferParserTest DifferParserTest.cpp)
target_link_libraries(
  DifferParserTest gtest gtest_main cpp-subprocess::subprocess 
)
target_include_directories(DifferParserTest PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(DifferParserTest)
MemoryCheck(DifferParserTest)
AddCoverage(DifferParserTest)
gtest_discover_tests(DifferParserTest)
