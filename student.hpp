#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "student_status.hpp"
#include "major.hpp"
#include "course.hpp"

class Student
{
private:
    Vector<Course*> courses;
    String name;
    Major major;
    StudentStatus status;
    int fac_number;
    int year;
    int group;
    double gpa;
    void copy_from(const Student& other);
    void free_memory();

public:
    Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();
};

#endif // STUDENT_HPP
