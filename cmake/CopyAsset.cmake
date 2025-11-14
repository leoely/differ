function(CopyAsset target)
  if (DEBUG)
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_SOURCE_DIR}/asset/"
            "$<TARGET_FILE_DIR:${target}>/asset/"
      COMMENT "Copying assets to build directory for MyTarget"
    )
  endif()
endfunction()
