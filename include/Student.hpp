//Copyright 2021 Morgan

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <string>
#include <any>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;


json takeJson(int argc, char** argv);


struct Student {
 public:
  Student();
  Student(std::string _name, std::any _group, std::any _avg, std::any debt);
  bool operator==(Student const & student) const;
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};


void print(Student& student, std::ostream& os);


void print(std::string s1, std::string s2,
           std::string s3, std::string s4, std::ostream& os);


void print(std::vector<Student>& students, std::ostream& os);


void from_json(const json& j, Student& s);


std::vector<Student> parsingJson(json& data);
#endif  //INCLUDE_STUDENT_HPP_
