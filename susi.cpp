#include "susi.hpp"

void SUSI::populate_data()
{
    // Add courses
    this->all_courses.push(Course("Calculus 1", CourseType::mandatory));
    this->all_courses.push(Course("Discrete Math", CourseType::mandatory));
    this->all_courses.push(Course("Algebra 1", CourseType::mandatory));
    this->all_courses.push(Course("Intro to Programming", CourseType::mandatory));
    this->all_courses.push(Course("Geometry", CourseType::mandatory));
    this->all_courses.push(Course("Languages, Automata, Computability", CourseType::mandatory));
    this->all_courses.push(Course("English", CourseType::free_elective));

    // Add majors
    this->all_majors.push(Major("Computer Science"));
    this->all_majors.push(Major("Software Engineering"));
    this->all_majors.push(Major("Informatics"));
    this->all_majors.push(Major("Information Systems"));

    // Assign courses to majors
    this->all_majors[0].add_course(&this->all_courses[0], 1);
    this->all_majors[1].add_course(&this->all_courses[6], 1);

    return;
}

void SUSI::run()
{
    this->populate_data();

    do
    {
        this->io_handler.input_command();
        String command = this->io_handler.get_command();

        // std::cout << command << std::endl;
        if (command == COMMAND_ENROLL)
        {
            this->handle_command_enroll();
        }
    }
    while (this->io_handler.get_command() != "quit");

}

void SUSI::handle_command_enroll()
{
    if (std::cin.peek() == '\n')
    {
        std::cout << "No args" << std::endl;
        std::cin.ignore();
        return;
    }

    this->io_handler.input_args(std::cin);

    Vector<String> arguments = this->io_handler.get_args();
    if (arguments.get_len() != 4)
    {
        std::cout << "Usage message" << std::endl;
        return;
    }

    if (!arguments[0].is_valid_number())
    {
        std::cout << "Invalid faculty number" << std::endl;
        return;
    }

    std::cout << arguments[0].to_int() << std::endl;
}
