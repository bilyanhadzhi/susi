#include <iostream>
#include <cstring>

#include "io_handler.hpp"

#include "constants.hpp"

void IOHandler::set_command(const char* command)
{
    this->command = command;
}

void IOHandler::input_command()
{
    std::cin >> this->command;
}

void IOHandler::input_args(std::istream& i_stream)
{
    this->clean_args();

    String args_string = "";
    args_string.input(i_stream, true);

    if (args_string == "")
    {
        return;
    }

    String curr_arg;
    int args_str_len = args_string.get_len();
    int i = 0;
    while (args_string[i] == ' ')
    {
        ++i;
    }

    while (i < args_str_len)
    {
        if (args_string[i] != ' ')
        {
            curr_arg += args_string[i];
            ++i;
        }
        else
        {
            while (args_string[i] == ' ')
            {
                ++i;
            }
            curr_arg += '\0';
            this->args.push(curr_arg);
            curr_arg = "";
        }
    }

    if (curr_arg != "")
    {
        this->args.push(curr_arg);
    }

    return;
}

String IOHandler::get_command() const
{
    return this->command;
}

Vector<String> IOHandler::get_args() const
{
    return this->args;
}

void IOHandler::clean_args()
{
    this->args.empty_vector();
}

bool IOHandler::check_number_of_arguments(int num_of_args) const
{
    return this->args.get_len() == num_of_args;
}

void IOHandler::print_usage(const char* command, const char* usage) const
{
    std::cout << "Usage: ";
    std::cout << command << " " << usage << std::endl;
}

void IOHandler::print_error(const char* desc) const
{
    std::cout << "Error: ";
    std::cout << desc << std::endl;
}
