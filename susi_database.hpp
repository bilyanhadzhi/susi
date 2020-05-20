#ifndef SUSI_DATABASE_HPP
#define SUSI_DATABASE_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "major.hpp"
#include "course.hpp"
#include "student.hpp"

class Database
{
private:
    Vector<Major> majors;
    Vector<Course> courses;
    Vector<Student> students;
    //! Dummy function to add some courses
    void populate_data();
public:
    Database();
    //! Add new student to database
    void add_student(Student student);
    // Functions for accessing the database
    //! Get all majors via pointers
    Vector<Major*> get_majors() const;
    //! Get all courses via pointers
    Vector<Course*> get_courses() const;
    //! Get all students via pointers
    Vector<Student*> get_students() const;
    //! Get majors with matching name (we shouldn't have repeats)
    Vector<Major*> get_majors_by_name(String name) const;
    //! Get courses with matching name (we shouldn't have repeats)
    Vector<Course*> get_courses_by_name(String name) const;
    //! Get students with matching faculty number
    Student* get_student_by_fac_number(int fac_number) const;
    //! Get all passed courses for a given student
    Vector<PassedCourse*> get_passed_courses_for_student(Student* student) const;
};

#endif // SUSI_DATABASE_HPP
