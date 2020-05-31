#ifndef COURSE_HPP
#define COURSE_HPP

#include "lib/string.hpp"
#include "course_type.hpp"

class Course
{
private:
    String name;
    CourseType type;

public:
    //! Default constructor with empty name and CourseType - none
    Course();
    //! Constructor with course name and a CourseType
    Course(const char* name, CourseType type);
    //! Get course name
    String get_name() const;
    //! Get type of course
    CourseType get_type() const;
    //! Get course type as a string
    const char* get_type_name() const;
    //! Print course information to output stream
    friend std::ostream& operator<<(std::ostream& o_stream, const Course& course);
    //! Write course to binary file
    bool write_to_bin(std::ofstream& of_stream);
    //! Read course from binary file
    bool read_from_bin(std::ifstream& if_stream);
};

#endif // COURSE_HPP
