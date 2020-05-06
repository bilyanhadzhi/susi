#include "major.hpp"

void Major::copy_from(const Major& other)
{
    Vector<Course>* new_courses = new Vector<Course>[other.max_years];
    for (int i = 0; i < other.max_years; ++i)
    {
        new_courses[i] = other.courses[i];
    }

    this->free_memory();
    this->max_years = other.max_years;
    this->courses = new_courses;
}

void Major::free_memory()
{
    delete[] this->courses;
}

Major::Major()
{
    this->max_years = 4;
    this->courses = new Vector<Course>[max_years];
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
