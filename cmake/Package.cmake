find_program(CPACK_PATH cpack REQUIRED)

add_custom_target(ApplePackage
  COMMAND ${CPACK_PATH} -G DragNDrop
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
