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
        else if (command == COMMAND_CHANGE)
        {
            this->handle_command_change();
        }
        else if (command == COMMAND_GRADUATE)
        {
            this->handle_command_graduate();
        }
        else if (command == COMMAND_INTERRUPT)
        {
            this->handle_command_interrupt();
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
        this->io_handler.print_error("No student with specified faculty number exists");
        return;
    }

    if (!student->can_advance())
    {
        this->io_handler.print_error("Cannot advance student with more than 2 pending mandatory courses");
        return;
    }

    student->advance_year();
    return;
}

void SUSI::handle_command_change()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_CHANGE, USAGE_CHANGE);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(3))
    {
        this->io_handler.print_usage(COMMAND_CHANGE, USAGE_CHANGE);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }

    if (arguments[1] == ARGUMENT_CHANGE_GROUP)
    {
        if (!arguments[2].is_valid_number(true) || arguments[2].to_int() < 1 || arguments[2].to_int() > MAX_GROUP)
        {
            this->io_handler.print_error("Invalid group number; group must be an integer in range [1, 8]");
            return;
        }

        Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

        if (!student)
        {
            this->io_handler.print_error("No student with specified faculty number exists");
            return;
        }

        student->set_group(arguments[2].to_int());
    }
    else if (arguments[1] == ARGUMENT_CHANGE_PROGRAM)
    {
        Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

        if (!student)
        {
            this->io_handler.print_error("No student with specified faculty number exists");
            return;
        }

        Vector<Major*> majors = this->database.get_majors_by_name(arguments[2]);

        if (majors.get_len() != 1)
        {
            this->io_handler.print_error("Could not find major");
            return;
        }

        if (!student->can_switch_major(majors[0]))
        {
            this->io_handler.print_error("Can not switch major – student has not passed all exams necessary");
            return;
        }

        student->set_major(majors[0]);
    }
    else if (arguments[1] == ARGUMENT_CHANGE_YEAR)
    {
        Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

        if (!student)
        {
            this->io_handler.print_error("No student with specified faculty number exists");
            return;
        }

        if (!arguments[2].is_valid_number(true))
        {
            this->io_handler.print_error("Invalid year number");
            return;
        }

        const int new_year = arguments[2].to_int();

        if (student->get_year() + 1 != new_year)
        {
            this->io_handler.print_error("Can not advance to any other year other than next");
            return;
        }

        if (!student->can_advance())
        {
            this->io_handler.print_error("Cannot advance student with more than 2 pending mandatory courses");
            return;
        }

        student->advance_year();
    }
}

void SUSI::handle_command_graduate()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_GRADUATE, USAGE_GRADUATE);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(1))
    {
        this->io_handler.print_usage(COMMAND_GRADUATE, USAGE_GRADUATE);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }

    Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

    if (!student)
    {
        this->io_handler.print_error("No student with specified faculty number exists");
        return;
    }

    if (!student->can_graduate())
    {
        this->io_handler.print_error("Student can not graduate with pending courses");
        return;
    }

    student->graduate();
}

void SUSI::handle_command_interrupt()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_INTERRUPT, USAGE_INTERRUPT);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(1))
    {
        this->io_handler.print_usage(COMMAND_GRADUATE, USAGE_GRADUATE);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }

    Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

    if (!student)
    {
        this->io_handler.print_error("No student with specified faculty number exists");
        return;
    }

    if (student->get_status() == StudentStatus::interrupted)
    {
        this->io_handler.print_error("Student has already interrupted");
        return;
    }

    student->set_status(StudentStatus::interrupted);
}

void SUSI::handle_command_resume()
{
    if (std::cin.peek() == '\n')
    {
        this->io_handler.print_usage(COMMAND_INTERRUPT, USAGE_INTERRUPT);
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    if (!this->io_handler.check_number_of_arguments(1))
    {
        this->io_handler.print_usage(COMMAND_GRADUATE, USAGE_GRADUATE);
        return;
    }

    Vector<String> arguments = this->io_handler.get_args();
    if (!arguments[0].is_valid_number(true))
    {
        this->io_handler.print_error("Invalid faculty number");
        return;
    }

    Student *student = this->database.get_student_by_fac_number(arguments[0].to_int());

    if (!student)
    {
        this->io_handler.print_error("No student with specified faculty number exists");
        return;
    }

    if (student->get_status() == StudentStatus::enrolled)
    {
        this->io_handler.print_error("Student is already enrolled");
        return;
    }

    student->set_status(StudentStatus::enrolled);
}
