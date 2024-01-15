#include <iostream>
#include <vector>

/**
 * Student class
 */
class Student {

  int m_age = 18;
  int m_avg = 100;
  std::string m_firstName = "First Name";
  std::string m_lastName = "Last Name";

public:

  // Default constructor.
  Student() { }

  Student(int age, int avg, std::string firstName, std::string lastName)
    : m_age(age)
    , m_avg(avg)
    , m_firstName(firstName)
    , m_lastName(lastName)
    {
    }

  int getAge() const {
    return m_age;
  }

  int getAvg() const {
    return m_avg;
  }

  std::string getFirstName() const {
    return m_firstName;
  }

  std::string getLastName() const {
    return m_lastName;
  }

  void print() const {
    std::cout << m_age  << " " << m_avg << " " << m_firstName << " " << m_lastName << std::endl;
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
