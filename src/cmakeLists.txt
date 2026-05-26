find_package(termcolor CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

add_executable(differ main.cpp)

find_path(TERMCOLOR_INCLUDE_DIRS "termcolor/termcolor.hpp")
target_include_directories(differ PRIVATE ${TERMCOLOR_INCLUDE_DIRS})

Optimize(differ)
MemoryCheck(differ)
AddCoverage(differ)

target_link_libraries(differ DifferParser LocationParser Parser generate assist validate termcolor::termcolor)

install(TARGETS differ DESTINATION bin)

add_subdirectory(Parser)
add_subdirectory(LocationParser)
add_subdirectory(DifferParser)
add_subdirectory(generate)
add_subdirectory(help)
add_subdirectory(validate)
