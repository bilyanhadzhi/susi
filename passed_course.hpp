#ifndef PASSED_COURSE_HPP
#define PASSED_COURSE_HPP

#include "course.hpp"

class PassedCourse: public Course
{
private:
    int grade;
    // void copy_from(const PassedCourse& other);
    //! Get whether grade is in range [2, 6]
    bool is_valid_grade(int grade);

public:
    PassedCourse();
    PassedCourse(Course* course, int grade);
    // PassedCourse(const PassedCourse& other);
};

#endif // PASSED_COURSE_HPP
