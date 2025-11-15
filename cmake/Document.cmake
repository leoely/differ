if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc")
  doxygen_add_docs(
    DifferDocs
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    COMMENT "Generating doxygen documentation for differ."
    ALL
  )
endif()
