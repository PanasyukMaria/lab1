#include "Student.hpp"

int main(int argc, char** argv)
{
 nlohmann::json data = takeJson(argc, argv);
 std::vector<Student> students = parsingJson(data);
 print(students, std::cout);
 //std::cout << argv[1] << std::endl;
}

