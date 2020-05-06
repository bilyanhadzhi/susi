#ifndef COURSE_HPP
#define COURSE_HPP

#include "lib/string.hpp"
#include "course_type.hpp"

class Course
{
private:
    String name;
    CourseType type;
    void copy_from(const Course& other);

public:
    Course();
    Course(const char* name, CourseType type);
    Course(const Course& other);
    Course& operator=(const Course& other);
    ~Course();
};

#endif // COURSE_HPP
