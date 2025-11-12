function(AddCoverage coverage)
  find_program(LCOV_PATH lcov REQUIRED)
  find_program(GENHTML_PATH genhtml REQUIRED)

  add_custom_target("${coverage}"
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage
    COMMAND ${LCOV_PATH} --ignore-errors inconsistent --capture --directory . --output-file "${coverage}.info"
    COMMAND ${GENHTML_PATH} "${coverage}.info" --output-directory coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )
endfunction()
