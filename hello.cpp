#include <iostream>
#include <vector>

/**
 * Student class
 */
class Student {

  int _age = 18;
  int _avg = 100;
  std::string _firstName = "First Name";
  std::string _lastName = "Last Name";

public:

  // Default constructor.
  Student() { }

  Student(int age, int avg, std::string firstName, std::string lastName)
    : _age(age)
    , _avg(avg)
    , _firstName(firstName)
    , _lastName(lastName)
    {
    }

  int getAge() const {
    return _age;
  }

  int getAvg() const {
    return _avg;
  }

  std::string getFirstName() const {
    return _firstName;
  }

  std::string getLastName() const {
    return _lastName;
  }

  void print() const {
    std::cout << _age  << " " << _avg << " " << _firstName << " " << _lastName << std::endl;
  }

};

/**
 * Course class
 */
class Course {

  std::string _name = "Course";
  std::vector<Student> _students;

public:
  Course() { }

  Course(const std::string& name) 
    : _name(name)
  {
  }

  void addStudent(const Student& student) {
    _students.push_back(student);
  }

  const std::vector<Student>& getStudents() const {
    return _students;
  }

  void loadFromFile(const std::string& fileName) {
    std::ifstream fin(fileName);
    std::string firstName, lastName;
    int age;
    int avg;

    // While we have first names.
    while (fin >> firstName) {
      fin >> lastName >> id >> avg;
      addStudent(Student(age, avg, firstName, lastName));
    }
  }

  void print() {
    for (const auto& student : _students) {
      student.print();
    }
  }

};

int main() {
  const Student s1;
  const Student s2(26, 80, "Caleb", "Jaggard");
  const Student s3(24, 100, "Kate", "Rathgen");

  Course c1("Applied Programming");
  c1.addStudent(s1);
  c1.addStudent(s2);
  c1.addStudent(s3);
  c1.addStudent(Student(30, 50, "Bob", "Smith"));

  c1.print();

  return 0;
}
