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
    Vector<Course*> pending_courses;
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
    void update_gpa();

public:
    Student();
    Student(int fac_number, Major* major, int group, String name, int year = 1, StudentStatus status = StudentStatus::enrolled);
    //! Get name of student
    String get_name() const;
    //! Get faculty number of student
    int get_fac_number() const;
    //! Get a list of all courses the student has not yet passed
    Vector<Course*> get_pending_courses() const;
    //! Increment student's year
    void advance_year();
    //! Change group of student; return whether successful
    bool set_group(int group);
    //! Set major
    void set_major(Major* major);
    //! Check whether student can advance to next year
    bool can_advance() const;
    //! Check if student can change major
    bool can_switch_major(Major* major) const;
    //! Check whether course has been passed
    bool has_passed_course(Course* course) const;

};

#endif // STUDENT_HPP
