#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <gtest/gtest.h>
#include <LocationParser/LocationParser.hpp>
#include <serializeStringListMap/serializeStringListMap.hpp>

using std::list;
using std::unordered_map;
using std::ifstream;

TEST(Class_LocationParser, test_that_the_loc_file_is_parsed_correctly) {
  shared_ptr<LocationParser> locationParser(new LocationParser());
  ifstream file("./asset/test.loc");
  string str;
  while (getline(file, str)) {
    locationParser->scanLine(str);
  }
  unordered_map<string, list<string>> location = locationParser->getLocation();
  string locationString = serializeStringListMap(location);
  EXPECT_EQ(locationString, "{'oracle':['/tmp/differ/oracle.sql',]'postgresql':['/tmp/differ/postgresql.sql',]'mysql':['/tmp/differ/mysql.sql',]'opensource':['/tmp/differ/mysql.sql','/tmp/differ/postgresql.sql',]}");

  list<string> fullList = locationParser->getFullList();
  string fullListString = "[";
  for (auto it = fullList.begin(); it != fullList.end(); it++) {
    int index = distance(fullList.begin(), it);
    if (index != static_cast<int>(fullList.size() - 1)) {
      fullListString.append("'" + *it + "',");
    } else {
      fullListString.append("'" + *it + "'");
    }
  }
  fullListString.append("]");
  EXPECT_EQ(fullListString, "['/tmp/differ/oracle.sql','/tmp/differ/postgresql.sql','/tmp/differ/mysql.sql']");
}
