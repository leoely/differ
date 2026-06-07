add_executable(previewTest previewTest.cpp)
target_link_libraries(
  previewTest gtest gtest_main cpp-subprocess::subprocess
)
target_include_directories(previewTest PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(previewTest)
MemoryCheck(previewTest)
AddCoverage(previewTest)
gtest_discover_tests(previewTest)
