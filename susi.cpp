#include "susi.hpp"

void SUSI::get_data()
{

}

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

}
