#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <ranges>
#include <help/help.hpp>
#include <generate/generate.hpp>
#include <validate/validate.hpp>
#include <preview/preview.hpp>
#include <look/look.hpp>
#include <clear/clear.hpp>
#include <location/location.hpp>
#include <repeat/repeat.hpp>
#include <history/history.hpp>
#include <sago/platform_folders.h>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::unordered_set;
using std::vector;
using std::string;
using std::views::join_with;
using std::ios_base;

void addCommandHistory(string commandName, vector<string>& parameters) {
  string documentPathString = sago::getDocumentsFolder();
  const fs::path documentPath = documentPathString;
  const fs::path homePath = documentPath.parent_path();
  fs::path differHistorysPath = homePath / ".differ_historys";
  if (!fs::exists(differHistorysPath)) {
    ofstream differHistorysFile(differHistorysPath);
    differHistorysFile.close();
  }
  ifstream differHistorysFile(differHistorysPath);
  string line;
  unordered_set<string> set;
  list<string> lines;
  while (getline(differHistorysFile, line)) {
    lines.push_back(line);
    set.insert(line);
  }
  auto joined_view = join_with(parameters, " ");
  string parametersString{joined_view.begin(), joined_view.end()};
  string history = commandName + " " + parametersString;
  if (!set.contains(history)) {
    ofstream differHistorysFile1(differHistorysPath, ios_base::app);
    differHistorysFile1 << history << "\n";
  } else {
    int sameIndex;
    int index = 0;
    ifstream differHistorysFile1(differHistorysPath);
    string line1;
    while (getline(differHistorysFile1, line1)) {
      if (line1 == history) {
        sameIndex = index;
      }
      index += 1;
    }
    int lastIndex = set.size() - 1;
    if (sameIndex != lastIndex) {
      auto it1 = next(lines.begin(), sameIndex);
      auto it2 = next(lines.begin(), lastIndex);
      iter_swap(it1, it2);
      ofstream differHistorysFile2(differHistorysPath);
      for (const auto& line : lines) {
        differHistorysFile2 << line << "\n";
      }
      differHistorysFile2.close();
    }
  }
}

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    help();
    exit(EXIT_SUCCESS);
  }
  string argument1 = argv[1];
  if (argument1 == "-h") {
    help();
    exit(EXIT_SUCCESS);
  } else if (argument1 == "--help") {
    help();
    exit(EXIT_SUCCESS);
  } else if (argument1 == "-v") {
    cout << "v1.1.0" << endl;
    exit(EXIT_SUCCESS);
  } else if (argument1 == "--version") {
    cout << "v1.1.0" << endl;
    exit(EXIT_SUCCESS);
  }
  vector<string> arguments;
  for (int i = 2; i < argc; i += 1) {
    string argument = argv[i];
    arguments.push_back(argument);
  }
  argc -= 2;
  if (argument1 == "generate") {
    generate(arguments);
    addCommandHistory("generate", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "validate") {
    validate(arguments);
    addCommandHistory("validate", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "look") {
    look(arguments);
    addCommandHistory("look", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "preview") {
    preview(arguments);
    addCommandHistory("preview", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "location") {
    location(arguments);
    addCommandHistory("location", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "clear") {
    clear(arguments);
    addCommandHistory("clear", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "history") {
    history(arguments);
    addCommandHistory("history", arguments);
    exit(EXIT_SUCCESS);
  } else if (argument1 == "repeat") {
    repeat(arguments);
    exit(EXIT_SUCCESS);
  } else {
    help();
    exit(EXIT_FAILURE);
  }
}
