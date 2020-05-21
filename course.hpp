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
    //! Get course type as a string
    const char* get_type_name() const;
    //! Print course information to output stream
    friend std::ostream& operator<<(std::ostream& o_stream, const Course& course);
};

#endif // COURSE_HPP
