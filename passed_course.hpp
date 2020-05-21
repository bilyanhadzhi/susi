#ifndef PASSED_COURSE_HPP
#define PASSED_COURSE_HPP

#include "course.hpp"

class PassedCourse: public Course
{
private:
    double grade;
    //! Get whether grade is in range [2, 6]
    void set_grade(double grade);

public:
    PassedCourse();
    PassedCourse(Course* course, double grade);
    //! Get grade of passed course
    double get_grade() const;
    //! Print passec course to output stream
    friend std::ostream& operator<<(std::ostream& o_stream, const PassedCourse& passed_course);
};

#endif // PASSED_COURSE_HPP
