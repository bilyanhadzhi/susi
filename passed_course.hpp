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
};

#endif // PASSED_COURSE_HPP
