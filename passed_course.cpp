#include <fstream>
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
    this->grade = 2;
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

bool PassedCourse::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    String course_name = this->get_name();
    if (!course_name.write_to_bin(of_stream))
    {
        return false;
    }

    CourseType type = this->get_type();
    if (!of_stream.write((char*)&type, sizeof(int)))
    {
        return false;
    }

    int grade = this->get_grade();
    if (!of_stream.write((char*)&grade, sizeof(int)))
    {
        return false;
    }

    return of_stream ? true : false;
}

bool PassedCourse::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    String course_name;
    if (!course_name.read_from_bin(if_stream))
    {
        return false;
    }

    CourseType type;
    if (!if_stream.read((char*)&type, sizeof(int)))
    {
        return false;
    }

    int grade = this->get_grade();
    if (!if_stream.read((char*)&grade, sizeof(int)))
    {
        return false;
    }

    this->name = course_name;
    this->type = type;
    this->grade = grade;

    return if_stream ? true : false;
}
