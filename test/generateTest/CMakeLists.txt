add_executable(generateTest generateTest.cpp)
target_link_libraries(
  generateTest gtest gtest_main cpp-subprocess::subprocess
)
target_include_directories(generateTest PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(generateTest)
MemoryCheck(generateTest)
AddCoverage(generateTest)
gtest_discover_tests(generateTest)
