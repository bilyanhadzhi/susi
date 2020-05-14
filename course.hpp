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
    //! Get course name
    String get_name() const;
    //! Get type of course
    CourseType get_type() const;
};

#endif // COURSE_HPP
