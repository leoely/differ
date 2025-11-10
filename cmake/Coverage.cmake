function(AddCoverage coverage)
  find_package(python3 REQUIRED COMPONENTS Interpreter)  # Required for gcovr
  find_program(PYTHON3_PATH python3 REQUIRED)
  find_program(GCOVR_PATH gcovr REQUIRED)

  add_custom_target("${coverage}"
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html -o "coverage/${coverage}.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating HTML coverage report..."
  )
endfunction()
