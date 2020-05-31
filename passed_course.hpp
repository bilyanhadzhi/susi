#ifndef PASSED_COURSE_HPP
#define PASSED_COURSE_HPP

#include "course.hpp"

//! A PassedCourse is a Course with a grade.

class PassedCourse: public Course
{
private:
    double grade;
    //! Get whether grade is in range [2, 6]
    void set_grade(double grade);

public:
    //! Default constructor with min grade
    PassedCourse();
    //! Constructor with pointer to course and grade (turns to min grade if not valid)
    PassedCourse(Course* course, double grade);
    //! Get grade of passed course
    double get_grade() const;
    //! Print passec course to output stream
    friend std::ostream& operator<<(std::ostream& o_stream, const PassedCourse& passed_course);
    //! Write PassedCourse to binary file
    bool write_to_bin(std::ofstream& of_stream);
    //! Read PassedCourse from binary file
    bool read_from_bin(std::ifstream& if_stream);
};

#endif // PASSED_COURSE_HPP
