#ifndef MAJOR_HPP
#define MAJOR_HPP

#include "course.hpp"

class Major
{
private:
    Course** courses;
    void copy_from(const Major& other);
    void free_memory();

public:
    Major();
    Major(const Major& other);
    Major& operator=(const Major& other);
    ~Major();
};

#endif // MAJOR_HPP
