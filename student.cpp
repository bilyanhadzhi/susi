#include <cassert>
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

bool Student::set_group(int group)
{
    if (group < 1 || group > MAX_GROUP)
    {
        // if group contains some random value out of range (i.e. when constructing)
        if (this->group < 1 || this->group > MAX_GROUP)
        {
            this->group = 1;
            return true;
        }

        // else, don't change
        return false;
    }

    this->group = group;
    return true;
}

String Student::get_name() const
{
    return this->name;
}

int Student::get_fac_number() const
{
    return this->fac_number;
}

Vector<Course*> Student::get_pending_courses() const
{
    return this->pending_courses;
}

void Student::advance_year()
{
    this->set_year(this->year + 1);
}

void Student::set_major(Major* major)
{
    assert(major != nullptr);

    this->major = major;
}

bool Student::can_advance() const
{
    int number_of_pending_courses = this->pending_courses.get_len();
    int courses_to_pass = 0;

    for (int i = 0; i < number_of_pending_courses; ++i)
    {
        if (this->pending_courses[i]->get_type() == CourseType::mandatory)
        {
            ++courses_to_pass;
        }
    }

    return courses_to_pass >= 0 && courses_to_pass <= 2;
}

bool Student::has_passed_course(Course* course) const
{
    assert (course != nullptr);
}

bool Student::can_switch_major(Major* major) const
{
    assert(major != nullptr);

    // Trying to switch to same major
    if (this->major == major)
    {
        return false;
    }

}

// TODO
void Student::update_gpa()
{

}
