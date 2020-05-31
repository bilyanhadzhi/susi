#include <cassert>
#include <iomanip>
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

bool Student::set_gpa(double gpa)
{
    if (gpa < MIN_COURSE_GRADE || gpa > MAX_COURSE_GRADE)
    {
        if (this->gpa < MIN_COURSE_GRADE || this->gpa > MAX_COURSE_GRADE)
        {
            this->gpa = MIN_COURSE_GRADE;
            return true;
        }

        return false;
    }

    this->gpa = gpa;
    return true;
}

bool Student::set_fac_number(int fac_number)
{
    if (fac_number < 0 || fac_number > MAX_FAC_NUMBER)
    {
        if (this->fac_number < 0 || this->fac_number > MAX_FAC_NUMBER)
        {
            this->fac_number = 0;
            return true;
        }

        return false;
    }

    this->fac_number = fac_number;
    return true;
}

bool Student::set_year(int year)
{
    if (this->status != StudentStatus::active)
    {
        return false;
    }

    if (year < 1 || year > MAX_YEAR)
    {
        if (this->year < 1 || this->year > MAX_YEAR)
        {
            this->year = 1;
            return true;
        }

        return false;
    }

    this->year = year;
    return true;
}

bool Student::set_group(int group)
{
    if (this->status != StudentStatus::active)
    {
        return false;
    }

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

bool Student::set_status(StudentStatus status)
{
    if (status == StudentStatus::graduated && !this->can_graduate())
    {
        return false;
    }

    this->status = status;
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

int Student::get_year() const
{
    return this->year;
}

double Student::get_gpa() const
{
    return this->gpa;
}

int Student::get_group() const
{
    return this->group;
}

Vector<Course*> Student::get_pending_courses() const
{
    return this->pending_courses;
}

Major* Student::get_major() const
{
    return this->major;
}

bool Student::advance_year()
{
    return this->status == StudentStatus::active ? this->set_year(this->year + 1) : false;
}

bool Student::set_major(Major* major)
{
    assert(major != nullptr);

    if (this->status != StudentStatus::active)
    {
        return false;
    }

    this->major = major;
    return true;
}

bool Student::can_advance() const
{
    if (this->status == StudentStatus::active)
    {
        return false;
    }

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
        if (this->passed_courses[i].get_name() == course->get_name())
        {
            if (this->passed_courses[i].get_grade() >= MIN_COURSE_GRADE + 1)
            {
                has_passed = true;
            }

            break;
        }
    }

    return has_passed;
}

bool Student::enroll_in(Course* course)
{
    assert(course != nullptr);

    const int passed_courses_len = this->passed_courses.get_len();
    for (int i = 0; i < passed_courses_len; ++i)
    {
        if (this->passed_courses[i].get_name() == course->get_name())
        {
            return false;
        }
    }

    this->pending_courses.push(course);
    return true;
}

Course* Student::get_enrolled_course(Course* course) const
{
    assert(course != nullptr);

    Course* found_course = nullptr;

    const int pending_courses_len = this->pending_courses.get_len();
    for (int i = 0; i < pending_courses_len && !found_course; ++i)
    {
        if (pending_courses[i] == course)
        {
            found_course = course;
        }
    }

    return found_course;
}

const Vector<PassedCourse>& Student::get_passed_courses() const
{
    return this->passed_courses;
}

bool Student::can_enroll(Course* course)
{
    assert(course != nullptr);

    if (this->is_enrolled_in(course))
    {
        return false;
    }

    if (this->has_passed_course(course))
    {
        return false;
    }

    return this->major->get_courses()[this->year - 1].get_first_occurrence(course) != -1;
}

bool Student::is_enrolled_in(Course* course) const
{
    return this->pending_courses.get_first_occurrence(course) != -1;
}

bool Student::can_switch_major(Major* major) const
{
    assert(major != nullptr);

    bool can_switch = true;

    if (this->status == StudentStatus::active)
    {
        can_switch = false;
    }

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
    return this->status == StudentStatus::active && this->year == this->major->get_max_years() && this->pending_courses.get_len() == 0;
}

bool Student::graduate()
{
    if (!this->can_graduate())
    {
        return false;
    }

    this->status = StudentStatus::graduated;
    return true;
}

StudentStatus Student::get_status() const
{
    return this->status;
}

// TODO
void Student::update_gpa()
{
    int number_of_courses = 0;
    double cumulative_grade = 0;

    const int num_pending_courses = this->pending_courses.get_len();
    number_of_courses += num_pending_courses;
    cumulative_grade += (num_pending_courses * 2);

    const int passed_courses_len = this->passed_courses.get_len();
    number_of_courses += passed_courses_len;
    for (int i = 0; i < passed_courses_len; ++i)
    {
        cumulative_grade += this->passed_courses[i].get_grade();
    }

    this->gpa = cumulative_grade / number_of_courses;
}

const char* Student::get_student_type_name() const
{
    switch (this->status)
    {
    case StudentStatus::none:
        return NAME_STUDENT_STATUS_NONE;
    case StudentStatus::active:
        return NAME_STUDENT_STATUS_ACTIVE;
    case StudentStatus::interrupted:
        return NAME_STUDENT_STATUS_INTERRUPTED;
    case StudentStatus::graduated:
        return NAME_STUDENT_STATUS_ACTIVE;
    default:
        return NAME_STUDENT_STATUS_NONE;
    }
}

std::ostream& operator<<(std::ostream& o_stream, const Student& student)
{
    o_stream << "| ";
    o_stream << std::setw(6) << student.fac_number << " | ";
    o_stream << std::setw(12) << student.name << " | ";
    o_stream << std::setw(10) << student.get_student_type_name() << " | ";
    o_stream << std::setw(20) << student.major->get_name() << " | ";
    o_stream << std::setw(5) << "Year " << student.year << " | ";
    o_stream << std::setw(6) << "Group " << student.group << " |";
    // o_stream << std::setw(6) << student.get_gpa() << " |";

    return o_stream;
}

bool Student::pass_course(Course* course, double grade)
{
    if (this->status != StudentStatus::active)
    {
        return false;
    }

    if (grade < MIN_COURSE_GRADE + 1 || grade > MAX_COURSE_GRADE)
    {
        return false;
    }

    // Find course in pending
    Course* found_course = this->get_enrolled_course(course);
    if (!found_course)
    {
        return false;
    }

    // push new instance of finished course
    this->passed_courses.push(PassedCourse(found_course, grade));

    // remove pointer to pending course
    int index_of_course = this->pending_courses.get_first_occurrence(found_course);
    this->pending_courses.remove(index_of_course);

    // update gpa
    this->update_gpa();

    return true;
}

void Student::add_passed_course(PassedCourse passed_course)
{
    if (this->has_passed_course(&passed_course))
    {
        return;
    }

    this->passed_courses.push(passed_course);
}

bool Student::is_enrolled_in_or_has_passed(Course* course)
{
    return this->is_enrolled_in(course) || this->has_passed_course(course);
}

double Student::get_grade_for_course(Course* course)
{
    PassedCourse* found_course = this->get_passed_course(course);

    return (found_course ? found_course->get_grade() : MIN_COURSE_GRADE);
}

PassedCourse* Student::get_passed_course(Course* course)
{
    assert (course != nullptr);

    PassedCourse* found_course = nullptr;

    const int passed_courses_len = this->passed_courses.get_len();

    for (int i = 0; i < passed_courses_len && !found_course; ++i)
    {
        if (this->passed_courses[i].get_name() == course->get_name())
        {
            if (this->passed_courses[i].get_grade() >= MIN_COURSE_GRADE + 1)
            {
                found_course = &this->passed_courses[i];
            }

            break;
        }
    }

    return found_course;
}
