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

void Student::set_status(StudentStatus status)
{
    if (status == StudentStatus::graduated && !this->can_graduate())
    {
        return;
    }

    this->status = status;
}

String Student::get_name() const
{
    return this->name;
}

int Student::get_fac_number() const
{
    return this->fac_number;
}

int Student::get_year() const
{
    return this->year;
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
    if (this->year == MAX_YEAR)
    {
        return false;
    }

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

    bool has_passed = false;

    // search in passed courses
    const int passed_courses_len = this->passed_courses.get_len();

    for (int i = 0; i < passed_courses_len && !has_passed; ++i)
    {
        if (this->passed_courses[i]->get_name() == course->get_name())
        {
            if (this->passed_courses[i]->get_grade() >= 3)
            {
                has_passed = true;
            }

            break;
        }
    }

    return has_passed;
}

bool Student::can_switch_major(Major* major) const
{
    assert(major != nullptr);

    bool can_switch = true;

    // Trying to switch to same major
    if (this->major == major)
    {
        can_switch = false;
    }

    const Vector<Course*>* major_courses = major->get_courses();

    // for each year of major until current (i.e. a container of courses)
    for (int i = 0; i < this->year && can_switch; ++i)
    {
        const int courses_curr_year_count = major_courses[i].get_len();

        // for each course of current year
        for (int j = 0; j < courses_curr_year_count && can_switch; ++j)
        {
            // check if has not been passed
            if (!this->has_passed_course(major_courses[i][j]))
            {
                can_switch = false;
            }
        }
    }

    return can_switch;
}

bool Student::can_graduate() const
{
    return this->year == this->major->get_max_years() && this->pending_courses.get_len() == 0;
}

void Student::graduate()
{
    if (!this->can_graduate())
    {
        return;
    }

    this->status = StudentStatus::graduated;
}

StudentStatus Student::get_status() const
{
    return this->status;
}

// TODO
void Student::update_gpa()
{

}
