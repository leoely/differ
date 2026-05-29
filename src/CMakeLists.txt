find_package(argparse CONFIG REQUIRED)

add_executable(differ main.cpp)

find_path(TERMCOLOR_INCLUDE_DIRS "termcolor/termcolor.hpp")
target_include_directories(differ PRIVATE ${TERMCOLOR_INCLUDE_DIRS})

Optimize(differ)
MemoryCheck(differ)
AddCoverage(differ)

target_link_libraries(differ help validate generate Parser DifferParser LocationParser Token Lexer LocationLexer DifferLexer locationTemplate differTemplate)

install(TARGETS differ DESTINATION bin)

add_subdirectory(LocationToken)
add_subdirectory(DifferToken)
add_subdirectory(Lexer)
add_subdirectory(LocationLexer)
add_subdirectory(DifferLexer)
add_subdirectory(locationTemplate)
add_subdirectory(differTemplate)
add_subdirectory(Parser)
add_subdirectory(LocationParser)
add_subdirectory(DifferParser)
add_subdirectory(generate)
add_subdirectory(help)
add_subdirectory(validate)
