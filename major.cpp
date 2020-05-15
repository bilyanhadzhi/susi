#include "major.hpp"

void Major::copy_from(const Major& other)
{
    Vector<Course*>* new_courses = new Vector<Course*>[other.max_years]();
    for (int i = 0; i < other.max_years; ++i)
    {
        new_courses[i] = other.courses[i];
    }

    this->free_memory();
    this->name = other.name;
    this->max_years = other.max_years;
    this->courses = new_courses;
}

void Major::free_memory()
{
    delete[] this->courses;
}

Major::Major(const char* name, int max_years)
{
    this->name = name;
    this->max_years = max_years;
    this->courses = new Vector<Course*>[max_years]();
}

Major::Major(const Major& other)
{
    this->copy_from(other);
}

Major& Major::operator=(const Major& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->free_memory();
    this->copy_from(other);

    return *this;
}

Major::~Major()
{
    this->free_memory();
}

void Major::add_course(Course* course, int year)
{
    if (year < 1 || year > this->max_years)
    {
        return;
    }

    this->courses[year - 1].push(course);
}

String Major::get_name() const
{
    return this->name;
}

int Major::get_max_years() const
{
    return this->max_years;
}

const Vector<Course*>* Major::get_courses() const
{
    return this->courses;
}
