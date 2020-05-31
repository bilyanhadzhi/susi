#include <fstream>
#include <iomanip>
#include "course.hpp"
#include "course_type.hpp"
#include "constants.hpp"

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

String Course::get_name() const
{
    return this->name;
}

CourseType Course::get_type() const
{
    return this->type;
}

const char* Course::get_type_name() const
{
    switch (this->type)
    {
    case CourseType::mandatory:
        return NAME_COURSE_TYPE_MANDATORY;
    case CourseType::free_elective:
        return NAME_COURSE_TYPE_FREE_ELECTIVE;
    case CourseType::none:
        return NAME_COURSE_TYPE_NONE;
    default:
        return NAME_COURSE_TYPE_NONE;
    }
}

std::ostream& operator<<(std::ostream& o_stream, const Course& course)
{
    std::cout << "| ";
    std::cout << std::setw(25) << course.get_name() << " | ";
    std::cout << std::setw(15) << course.get_type_name() << " | ";
    std::cout << std::setw(10) << "No grade" << " |";

    return o_stream;
}

bool Course::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    this->name.write_to_bin(of_stream);
    of_stream.write((char*)&this->type, sizeof(int));

    return of_stream ? true : false;
}

bool Course::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    this->name.read_from_bin(if_stream);
    if_stream.read((char*)&this->type, sizeof(int));

    return if_stream ? true : false;
}
