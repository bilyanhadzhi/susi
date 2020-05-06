#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "student_status.hpp"
#include "major.hpp"
#include "course.hpp"
#include "passed_course.hpp"

class Student
{
private:
    Vector<Course*> courses;
    Vector<PassedCourse*> passed_courses;
    String name;
    double gpa;
    Major* major;
    StudentStatus status;
    int fac_number;
    int year;
    int group;
    void set_gpa(double gpa);
    void set_fac_number(int fac_number);
    void set_year(int year);
    void set_group(int group);
    void update_gpa();

public:
    Student();
    Student(int fac_number, Major* major, int group, String name);
};

#endif // STUDENT_HPP
