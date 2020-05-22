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
    //! Get students by major and year
    Vector<Student*> get_students_by_major_and_year(Major* major, int year) const;
    //! Get a (sorted) list of students by course and year
    Vector<Student*> get_students_by_course_and_year(Course* course, int year) const;
    //! Sort a list of students (pointers) by their faculty number
    void sort_list_of_students_by_fac_number(Vector<Student*>& list) const;
    //! Filtera list of students by their major
    Vector<Student*> filter_students_by_major(const Vector<Student*>& list, Major* major) const;
};

#endif // SUSI_DATABASE_HPP
