function(AddCoverage target)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${target} PRIVATE -coverage)
    target_link_options(${target} PRIVATE -coverage)

    find_program(LCOV_PATH lcov REQUIRED)
    find_program(GENHTML_PATH genhtml REQUIRED)

    add_custom_target("${target}_coverage"
      COMMAND ${CMAKE_COMMAND} -E make_directory coverage
      COMMAND ${LCOV_PATH} --ignore-errors inconsistent --capture --directory . --output-file "${target}_coverage.info"
      COMMAND ${GENHTML_PATH} "${target}_coverage.info" --output-directory coverage
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
  endif()
endfunction()
