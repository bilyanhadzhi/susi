#ifndef MAJOR_HPP
#define MAJOR_HPP

#include "lib/vector.hpp"
#include "course.hpp"

//! The Major class holds n vectors of Course*, where n is the years of the education

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
    //! Default constructor
    Major(const char* name = "", int max_years = MAX_YEAR);
    //! Copy constructor
    Major(const Major& other);
    //! Turn into a copy of another major
    Major& operator=(const Major& other);
    //! Delete dynamic array of course-vectors
    ~Major();
    //! Add course to year
    void add_course(Course* course, int year);
    //! Get name of Major
    String get_name() const;
    //! Get course years
    int get_max_years() const;
    //! Get courses (can't be changed)
    const Vector<Course*>* get_courses() const;
    //! Write major to binary file
    bool write_to_bin(std::ofstream& of_stream);
    //! Read major from binary file
    bool read_from_bin(std::ifstream& if_stream);
};

#endif // MAJOR_HPP
