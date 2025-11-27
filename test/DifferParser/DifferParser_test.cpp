#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include <fstream>
#include <regex>
#include <gtest/gtest.h>
#include <DifferParser/DifferParser.hpp>
#include <LocationParser/LocationParser.hpp>
#include <serializeStringListMap/serializeStringListMap.hpp>

using std::list;
using std::unordered_map;
using std::string;
using std::ifstream;
using std::regex;
using std::shared_ptr;

TEST(Class_DifferParser, differ_files_can_be_parsed_correctly) {
  shared_ptr<LocationParser> locationParser(new LocationParser());
  ifstream file1("./asset/test.loc");
  string str1;
  while (getline(file1, str1)) {
    locationParser->scanLine(str1);
  }
  unordered_map<string, list<string>> location = locationParser->getLocation();
  list<string> fullList = locationParser->getFullList();
  shared_ptr<DifferParser> differParser(new DifferParser(fullList, location));
  ifstream file2("./asset/test.differ");
  string str2;
  while (getline(file2, str2)) {
    differParser->scanLine(str2);
  }
  unordered_map<string, list<string>> differ = differParser->getDiffer();
  string differString = serializeStringListMap(differ);
  regex quotation_re("\"");
  string escapeDifferString;
  regex_replace(back_inserter(escapeDifferString), differString.begin(), differString.end(), quotation_re, "\"");
  EXPECT_EQ(escapeDifferString, "{'/tmp/differ/oracle.sql':['-- The database is charged and subsequent use requires attention.',' ','-- This sql is used to create a database.','-- database not be installed.',]'/tmp/differ/postgresql.sql':['-- The databasea is open source and can be used for free and safely.',' ','-- This sql is used to create a database.','DROP TABLE IF EXISTS \"users\";','CREATE TABLE \"public\".\"users\" (','    \"id\" bigint NOT NULL,','   \"name\" text,','   \"age\" integer,','   \"gender\" integer,','   \"city\" text,','   \"country\" text,','   CONSTRAINT \"users_pkey\" PRIMARY KEY (\"id\")',') WITH (oids = false);',]'/tmp/differ/mysql.sql':['-- The databasea is open source and can be used for free and safely.',' ','-- This sql is used to create a database.','DROP TABLE IF EXISTS `users`;','CREATE TABLE `users` (',' `id` bigint NOT NULL,',' `name` text,',' `age` int DEFAULT NULL,',' `gender` int DEFAULT NULL,',' `city` text,',' `country` text,',' PRIMARY KEY (`id`)',') ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;',]}");
}
