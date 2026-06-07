add_executable(lookTest lookTest.cpp)
target_link_libraries(
  lookTest gtest gtest_main cpp-subprocess::subprocess
)
target_include_directories(lookTest PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(lookTest)
MemoryCheck(lookTest)
AddCoverage(lookTest)
gtest_discover_tests(lookTest)
