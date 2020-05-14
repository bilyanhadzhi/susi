#include "susi.hpp"

void SUSI::run()
{
    do
    {
        this->io_handler.input_command();
        String command = this->io_handler.get_command();

        // std::cout << command << std::endl;
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
    if (!arguments[0].is_valid_number())
    {
        std::cout << "Error: Invalid faculty number" << std::endl;
        return;
    }
    if (!arguments[2].is_valid_number(true))
    {
        std::cout << "Error: Invalid group number" << std::endl;
        return;
    }

    // Validate major
    Vector<Major*> majors_matching_name = this->database.get_majors_by_name(arguments[1]);

    if (majors_matching_name.get_len() != 1)
    {
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
    if (!arguments[0].is_valid_number())
    {
        std::cout << "Error: Invalid faculty number" << std::endl;
        return;
    }
}

// Student& SUSI::get_student
