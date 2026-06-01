add_executable(DifferParser_test DifferParser_test.cpp)
target_link_libraries(
  DifferParser_test gtest gtest_main serializeStringListMap
  Lexer DifferLexer LocationLexer locationTemplate differTemplate
  Parser LocationParser DifferParser
)
target_include_directories(DifferParser_test PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(DifferParser_test)
MemoryCheck(DifferParser_test)
AddCoverage(DifferParser_test)
gtest_discover_tests(DifferParser_test)
