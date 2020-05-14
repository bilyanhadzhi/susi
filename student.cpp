#include "student.hpp"
#include "student_status.hpp"
#include "constants.hpp"

Student::Student(): name(""), major(nullptr), status(StudentStatus::none)
{
    this->gpa = 0;
    this->fac_number = 0;
    this->year = 0;
    this->group = 0;
}

Student::Student(int fac_number, Major* major, int group, String name, int year, StudentStatus status):
    name(name), major(major), status(status)
{
    this->year = year;
    this->fac_number = fac_number;
    this->group = group;
    this->gpa = 0;
}

void Student::set_gpa(double gpa)
{
    if (gpa < MIN_COURSE_GRADE || gpa > MAX_COURSE_GRADE)
    {
        this->gpa = MIN_COURSE_GRADE;
        return;
    }

    this->gpa = gpa;
}

void Student::set_fac_number(int fac_number)
{
    if (fac_number < 0 || fac_number > MAX_FAC_NUMBER)
    {
        this->fac_number = 0;
        return;
    }

    this->fac_number = fac_number;
}

void Student::set_year(int year)
{
    if (year < 1 || year > MAX_YEAR)
    {
        this->year = 1;
        return;
    }

    this->year = year;
}

void Student::set_group(int group)
{
    if (group < 1 || group > MAX_GROUP)
    {
        this->group = 1;
        return;
    }

    this->group = group;
}

String Student::get_name() const
{
    return this->name;
}

int Student::get_fac_number() const
{
    return this->fac_number;
}

// TODO
void Student::update_gpa()
{

}
