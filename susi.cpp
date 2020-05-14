#include "susi.hpp"
#include "course_type.hpp"

void SUSI::run()
{
    do
    {
        this->io_handler.input_command();
        String command = this->io_handler.get_command();

        if (command == COMMAND_ENROLL)
        {
            this->handle_command_enroll();
        }
        else if (command == COMMAND_ADVANCE)
        {
            this->handle_command_advance();
        }
    }
    while (this->io_handler.get_command() != "quit");
}

void SUSI::handle_command_enroll()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_ENROLL, USAGE_ENROLL);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(4))
    {
        this->io_handler.print_usage(COMMAND_ENROLL, USAGE_ENROLL);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }
    if (!arguments[2].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid group number");
        return;
    }

    // Validate major
    Vector<Major*> majors_matching_name = this->database.get_majors_by_name(arguments[1]);

    if (majors_matching_name.get_len() != 1)
    {
        this->io_handler.print_error("Could not determine major");
        return;
    }

    Student new_student(arguments[0].to_int(), majors_matching_name[0], arguments[2].to_int(), arguments[3]);
    this->database.add_student(new_student);
}

void SUSI::handle_command_advance()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_ADVANCE, USAGE_ADVANCE);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(1))
    {
        this->io_handler.print_usage(COMMAND_ADVANCE, USAGE_ADVANCE);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }

    // get student by fn
    Student* student = this->database.get_student_by_fac_number(arguments[0].to_int());

    if (!student)
    {
        this->io_handler.print_error("No student with specified id exists");
        return;
    }

    // check if student has too many courses to pass
    Vector<Course*> pending_courses = student->get_pending_courses();
    int pending_courses_len = pending_courses.get_len();
    int courses_to_pass = 0;

    for (int i = 0; i < pending_courses_len; ++i)
    {
        if (pending_courses[i]->get_type() == CourseType::mandatory)
        {
            ++courses_to_pass;
        }
    }

    if (courses_to_pass > 2)
    {
        this->io_handler.print_error("Cannot advance student – too many courses to pass");
        return;
    }

    student->advance_year();
    return;
}
