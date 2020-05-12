#ifndef SUSI_HPP
#define SUSI_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "io_handler.hpp"
#include "student.hpp"


class SUSI
{
private:
    // A class that deals with getting commands
    IOHandler io_handler;
    // 'Database':
    Vector<Major> all_majors;
    Vector<Course> all_courses;
    Vector<Student> all_students;
    // Dummy function to add some courses
    void populate_data();
    // Functions to handle each command
    void handle_command_enroll();
    void handle_command_advance();
    void handle_command_change();
    void handle_command_graduate();
    void handle_command_interrupt();
    void handle_command_resume();
    void handle_command_print();
    void handle_command_print_all();
    void handle_command_enroll_in();
    void handle_command_add_grade();
    void handle_command_protocol();
    void handle_command_report();
    // Functions for accessing the 'database'
    Vector<Major*> get_majors_by_name(String name) const;

public:
    void run();
};

#endif // SUSI_HPP
