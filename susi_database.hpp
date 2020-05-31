#ifndef SUSI_DATABASE_HPP
#define SUSI_DATABASE_HPP

#include <fstream>
#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "major.hpp"
#include "course.hpp"
#include "student.hpp"

//! The database class stores all the courses, majors and students.

/*!
    If a file is loaded, is_loaded will be true and file_loaded will hold the name of that file.
    Filenames are relative to the folder db/ i.e. "database.db" means the file at "db/database.db"
*/

class Database
{
private:
    Vector<Course> courses;
    Vector<Major> majors;
    Vector<Student> students;
    String file_loaded;
    bool is_loaded;
    //! Dummy function to add some courses
    void populate_data();
public:
    //! Default constructor
    Database();
    //! Add new student to database
    void add_student(Student student);
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
    //! Empty the database
    void empty();
    //! Save information to binary file
    bool save(String filename = "");
    //! Load information
    bool load(String filename = "");
    //! Make empty file at destination
    void make_empty_file(String filename);
    //! Close file without saving
    bool close();
    //! Check if there is a db file opened
    bool get_is_loaded();
};

#endif // SUSI_DATABASE_HPP
