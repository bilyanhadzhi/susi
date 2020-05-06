#include "passed_course.hpp"

bool PassedCourse::is_valid_grade(int grade)
{
    bool result = true;

    if (grade < 2 || grade > 6)
    {
        result = false;
    }

    return result;
}

PassedCourse::PassedCourse()
{
    this->grade = 0;
}

PassedCourse::PassedCourse(Course* course, int grade): Course(*course)
{
    this->grade = this->is_valid_grade(grade) ? grade : 0;
}
