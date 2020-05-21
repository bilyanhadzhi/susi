#ifndef MAJOR_HPP
#define MAJOR_HPP

#include "lib/vector.hpp"
#include "course.hpp"

class Major
{
private:
    String name;
    //! Dynaminc container of course-vectors for each year (index 0 -> courses for year 1)
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
    //! Get course years
    int get_max_years() const;
    //! Get courses (can't be changed)
    const Vector<Course*>* get_courses() const;
};

#endif // MAJOR_HPP
