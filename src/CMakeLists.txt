add_executable(differ main.cpp)

find_path(TERMCOLOR_INCLUDE_DIRS "termcolor/termcolor.hpp")
target_include_directories(differ PRIVATE ${TERMCOLOR_INCLUDE_DIRS})

Optimize(differ)
MemoryCheck(differ)
AddCoverage(differ)

target_link_libraries(
  differ assist validate validateHelp generate
  ArgumentsResolver FilePath
  Parser DifferParser LocationParser VariableParser
  LocationMerge VariableMerge
  Lexer LocationLexer DifferLexer VariableLexer
  locationTemplate differTemplate variableTemplate
)

install(TARGETS differ DESTINATION bin)

add_subdirectory(Lexer)
add_subdirectory(LocationLexer)
add_subdirectory(DifferLexer)
add_subdirectory(VariableLexer)
add_subdirectory(locationTemplate)
add_subdirectory(differTemplate)
add_subdirectory(variableTemplate)
add_subdirectory(Parser)
add_subdirectory(LocationParser)
add_subdirectory(DifferParser)
add_subdirectory(VariableParser)
add_subdirectory(VariableMerge)
add_subdirectory(LocationMerge)
add_subdirectory(ArgumentsResolver)
add_subdirectory(FilePath)
add_subdirectory(generate)
add_subdirectory(help)
add_subdirectory(validate)
add_subdirectory(validateHelp)
