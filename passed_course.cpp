#include "passed_course.hpp"
#include "constants.hpp"

void PassedCourse::set_grade(double grade)
{
    if (grade < MIN_COURSE_GRADE || grade > MAX_COURSE_GRADE)
    {
        this->grade = MIN_COURSE_GRADE;
        return;
    }

    this->grade = grade;
}

PassedCourse::PassedCourse()
{
    this->grade = 0;
}

PassedCourse::PassedCourse(Course* course, double grade): Course(*course)
{
    this->set_grade(grade);
}
