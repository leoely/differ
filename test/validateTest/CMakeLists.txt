add_executable(validateTest validateTest.cpp)
target_link_libraries(
  validateTest gtest gtest_main cpp-subprocess::subprocess
)
target_include_directories(validateTest PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)
CopyAsset(validateTest)
MemoryCheck(validateTest)
AddCoverage(validateTest)
gtest_discover_tests(validateTest)
