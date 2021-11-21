//Copyright 2021 Morgan

#define TEST_CPP_
#ifdef TEST_CPP_

#include <gtest/gtest.h>
#include <Student.hpp>


#ifndef _JSON_DIR
#define JSON_DIR "nobody"
#else
#define JSON_DIR _JSON_DIR
#endif


TEST(printTest, StudentItem)
{
  std::stringstream ss;
  Student s("test", (std::string)"test", (size_t)4, std::vector<std::string>());
  print(s, ss);
  ASSERT_EQ("| test                | test      | 4         | 0         |\n"
      "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, StudentsArray) {
    std::stringstream ss;
    std::vector<Student> students;
    students.emplace_back("test", (std::string)"test",
                          (size_t)4, std::vector<std::string>());
    students.emplace_back("test", (size_t)2,
                          (double)4.33, std::vector<std::string>());
    print(students, ss);
    ASSERT_EQ("| name                | group     | avg       | debt      |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | test      | 4         | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n"
        "| test                | 2         | 4.33      | 0         |\n"
        "|---------------------|-----------|-----------|-----------|\n",  ss.str());
}
TEST(printTest, json)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vera Voronova\",\n"
      "      \"group\": \"33\",\n"
      "      \"avg\": \"5.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Peter Parker\",\n"
      "      \"group\": 32,\n"
      "      \"avg\": 2.75,\n"
      "      \"debt\": \"GoLang\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json _json = json::parse(jsonData);
  std::vector<Student> students_parsed = parsingJson(_json);
  std::stringstream ss;
  print(students_parsed, ss);
  ASSERT_EQ("| name                | group     | avg       | debt      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Vera Voronova       | 33        | 5.25      | null      |\n"
      "|---------------------|-----------|-----------|-----------|\n"
      "| Peter Parker        | 32        | 2.75      | GoLang    |\n"
      "|---------------------|-----------|-----------|-----------|\n", ss.str());
}

TEST(parseTest, jsonParse)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vera Voronova\",\n"
      "      \"group\": \"33\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\": null\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Peter Parker\",\n"
      "      \"group\": 34,\n"
      "      \"avg\": 2.25,\n"
      "      \"debt\": \"GoLang\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
    nlohmann::json _json = json::parse(jsonData);
    std::vector<Student> students_parsed = parsingJson(_json);
    std::vector<Student> student_inited = {
        Student("Vera Voronova", (std::string)"33",
                (std::string)"4.25", nullptr),
        Student("Peter Parker", (size_t)34,
                (double)2.25, (std::string)"GoLang")
    };
    ASSERT_EQ(student_inited, students_parsed);
}
TEST(parseTest, fromFile)
{
  std::string jsonData = "{\n"
      "  \"items\": [\n"
      "    {\n"
      "      \"name\": \"Vera Voronova\",\n"
      "      \"group\": \"33\",\n"
      "      \"avg\": \"4.25\",\n"
      "      \"debt\":  [\n"
      "        \"Java\",\n"
      "        \"C++\",\n"
      "        \"Python\"\n"
      "      ]\n"
      "    },\n"
      "    {\n"
      "      \"name\": \"Peter Parker\",\n"
      "      \"group\": 34,\n"
      "      \"avg\": 2.25,\n"
      "      \"debt\": \"GoLang\"\n"
      "    }\n"
      "  ],\n"
      "  \"_meta\": {\n"
      "    \"count\": 2\n"
      "  }\n"
      "}";
  nlohmann::json json1 = json::parse(jsonData);
  std::string path = JSON_DIR;
  path+="/test1.json";
  char* argv[] ={(char*)"", (char*)(path.c_str())};
  nlohmann::json json2 = takeJson(2, argv);
  ASSERT_EQ(json1, json2) << "Test passed!";
}

TEST(errorCheck, lessArgsTest)
{
  try {
    std::string path = JSON_DIR;
    path+="/test1.json";
    char* argv[] ={(char*)"", (char*)(path.c_str())};
    nlohmann::json json2 = takeJson(1, argv);
    FAIL() << "Expected: The file path was not passed";
  }
  catch(std::runtime_error const & err) {
    EXPECT_EQ(err.what(),std::string("The file path was not passed"));
  }
  catch(...) {
    FAIL() << "Expected The file path was not passed";
  }
}

#endif // TEST_CPP_