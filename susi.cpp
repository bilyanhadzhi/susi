#include "susi.hpp"

void SUSI::populate_data()
{
    // Add courses
    this->all_courses.push(Course("Calc_1", CourseType::mandatory));
    this->all_courses.push(Course("Discrete_Math", CourseType::mandatory));
    this->all_courses.push(Course("Algebra_1", CourseType::mandatory));
    this->all_courses.push(Course("Intro_to_Programming", CourseType::mandatory));
    this->all_courses.push(Course("Geometry", CourseType::mandatory));
    this->all_courses.push(Course("Languages_Automata_Computability", CourseType::mandatory));
    this->all_courses.push(Course("English", CourseType::free_elective));

    // Add majors
    this->all_majors.push(Major("Computer_Science"));
    this->all_majors.push(Major("Software_Engineering"));
    this->all_majors.push(Major("Informatics"));
    this->all_majors.push(Major("Information_Systems"));

    // Assign courses to majors
    this->all_majors[0].add_course(&this->all_courses[0], 1);
    this->all_majors[1].add_course(&this->all_courses[6], 1);

    // Add students
    this->all_students.push(Student(81980, &this->all_majors[0], 7, "Bilyan"));
    this->all_students.push(Student(81964, &this->all_majors[0], 7, "Ivana"));

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
    if (!arguments[2].is_valid_number(true))
    {
        std::cout << "Invalid group number" << std::endl;
        return;
    }

    Vector<Major*> majors_matching_name = this->get_majors_by_name(arguments[1]);

    // Can't create student
    if (majors_matching_name.get_len() != 1)
    {
        return;
    }

    Student new_student(arguments[0].to_int(), majors_matching_name[0], arguments[2].to_int(), arguments[3]);
    this->all_students.push(new_student);

    for (int i = 0; i < this->all_students.get_len(); ++i)
    {
        std::cout << this->all_students[i].get_name() << std::endl;
    }

}

Vector<Major*> SUSI::get_majors_by_name(String name) const
{
    Vector<Major*> filtered;

    const int majors_len = this->all_majors.get_len();
    for (int i = 0; i < majors_len; ++i)
    {
        if (this->all_majors[i].get_name() == name)
        {
            filtered.push(&this->all_majors[i]);
        }
    }

    return filtered;
}
