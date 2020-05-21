#include <iomanip>
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

double PassedCourse::get_grade() const
{
    return this->grade;
}

std::ostream& operator<<(std::ostream& o_stream, const PassedCourse& passed_course)
{
    std::cout << "| ";
    std::cout << std::setw(25) << passed_course.get_name() << " | ";
    std::cout << std::setw(15) << passed_course.get_type_name() << " | ";
    std::cout << std::setw(10) << std::fixed << std::setprecision(2) << passed_course.get_grade() << " |";

    return o_stream;
}
