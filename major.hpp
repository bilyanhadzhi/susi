#ifndef MAJOR_HPP
#define MAJOR_HPP

#include "lib/vector.hpp"
#include "course.hpp"

class Major
{
private:
    String name;
    //! Container of courses for each year (index 0 -> year 1)
    Vector<Course*>* courses;
    int max_years;
    void copy_from(const Major& other);
    void free_memory();

public:
    Major(const char* name = "", int max_years = MAX_YEAR);
    Major(const Major& other);
    Major& operator=(const Major& other);
    ~Major();
    //! Add course to year
    void add_course(Course* course, int year);
    //! Get name of Major
    String get_name() const;
};

#endif // MAJOR_HPP
