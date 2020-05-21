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
    Vector<PassedCourse> passed_courses;
    String name;
    double gpa;
    Major* major;
    StudentStatus status;
    int fac_number;
    int year;
    int group;
    bool set_gpa(double gpa);
    bool set_fac_number(int fac_number);
    bool set_year(int year);
    void update_gpa();

public:
    Student();
    Student(int fac_number, Major* major, int group, String name, int year = 1, StudentStatus status = StudentStatus::active);
    //! Get name of student
    String get_name() const;
    //! Get faculty number of student
    int get_fac_number() const;
    //! Get current year of student
    int get_year() const;
    //! Get pointer to student's major
    Major* get_major() const;
    //! Get student status
    StudentStatus get_status() const;
    //! Get a list of all courses the student has not yet passed
    Vector<Course*> get_pending_courses() const;
    //! Get course if student is enrolled; return nullptr otherwise
    Course* get_enrolled_course(Course* course) const;
    //! Remove course pointer from pending and create an instance of a finished course
    bool pass_course(Course* course, int grade);
    //! Increment student's year
    void advance_year();
    //! Change group of student; return whether successful
    bool set_group(int group);
    //! Set major
    void set_major(Major* major);
    //! Change student's status
    void set_status(StudentStatus status);
    //! Check whether this year student can enroll in course
    bool can_enroll(Course* course);
    //! Check whether student can advance to next year
    bool can_advance() const;
    //! Check if student is already enrolled in course
    bool is_enrolled_in(Course* course) const;
    //! Check if student can change major
    bool can_switch_major(Major* major) const;
    //! Check whether student can graduate
    bool can_graduate() const;
    //! Check whether course has been passed
    bool has_passed_course(Course* course) const;
    //! Enroll student in course (only if not already enrolled/passed)
    bool enroll_in(Course* course);
    //! Mark student as graduated (only if they can)
    void graduate();
    //! Get student's status as string
    const char* get_student_type_name() const;
    //! Print student
    friend std::ostream& operator<<(std::ostream& o_stream, const Student& student);


};

#endif // STUDENT_HPP
