#include "course.hpp"
#include "course_type.hpp"

Course::Course()
{
    this->name = "";
    this->type = CourseType::none;
}

Course::Course(const char* name, CourseType type)
{
    this->name = name;
    this->type = type;
}

Course::Course(const Course& other)
{
    this->copy_from(other);
}

void Course::copy_from(const Course& other)
{
    this->name = other.name;
    this->type = other.type;
}

String Course::get_name() const
{
    return this->name;
}

CourseType Course::get_type() const
{
    return this->type;
}
