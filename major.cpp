#include <fstream>
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
    if (this->courses != nullptr)
    {
        delete[] this->courses;
    }
}

Major::Major(const char* name, int max_years)
{
    assert(max_years >= 0);

    this->name = name;
    this->max_years = max_years;
    this->courses = new Vector<Course*>[max_years]();
}

Major::Major(const Major& other)
{
    this->courses = nullptr;
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

bool Major::write_to_bin(std::ofstream& of_stream)
{
    if (!of_stream)
    {
        return false;
    }

    if (!this->name.write_to_bin(of_stream))
    {
        return false;
    }

    if (!of_stream.write((char*)&this->max_years, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < this->max_years; ++i)
    {
        const int courses_for_year_count = this->courses[i].get_len();
        if (!of_stream.write((char*)&courses_for_year_count, sizeof(int)))
        {
            return false;
        }

        for (int j = 0; j < courses_for_year_count; ++j)
        {
            if (!this->courses[i][j]->write_to_bin(of_stream))
            {
                return false;
            }
        }
    }

    return true;
}

bool Major::read_from_bin(std::ifstream& if_stream)
{
    if (!if_stream)
    {
        return false;
    }

    if (!this->name.read_from_bin(if_stream))
    {
        return false;
    }

    if (!if_stream.read((char*)&this->max_years, sizeof(int)))
    {
        return false;
    }

    this->courses = new Vector<Course*>[this->max_years];

    for (int i = 0; i < this->max_years; ++i)
    {
        int courses_for_year_count;

        if (!if_stream.read((char*)&courses_for_year_count, sizeof(int)))
        {
            return false;
        }

        for (int j = 0; j < courses_for_year_count; ++j)
        {
            this->courses[i][j] = new Course();
            this->courses[i][j]->read_from_bin(if_stream);
        }
    }
}
