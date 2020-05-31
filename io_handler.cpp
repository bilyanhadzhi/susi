#include <iostream>
#include <cstring>

#include "io_handler.hpp"

#include "lib/string.hpp"
#include "constants.hpp"

void IOHandler::set_command(String command)
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

void IOHandler::print_prompt() const
{
    std::cout << "(susi) $ ";
}

void IOHandler::print_usage(String command, String usage, bool with_prefix) const
{
    if (with_prefix)
    {
        std::cout << "Usage: ";
    }
    std::cout << command;
    std::cout << " ";

    if (usage.get_len() < 1)
    {
        std::cout << "(no args)\n";
    }
    else
    {
        std::cout << usage << "\n";
    }
}

void IOHandler::print_error(String desc) const
{
    std::cout << "Error: ";
    std::cout << desc << std::endl;
}

void IOHandler::print_unknown_command() const
{
    std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
}

void IOHandler::print_success(String message) const
{
    std::cout << "Success: ";
    std::cout << message << std::endl;
}

void IOHandler::print_help() const
{
    std::cout << "\nSUSI Commands:\n\n";

    this->print_usage(COMMAND_ENROLL, USAGE_ENROLL, false);
    this->print_usage(COMMAND_ADVANCE, USAGE_ADVANCE, false);
    this->print_usage(COMMAND_CHANGE, USAGE_CHANGE, false);
    this->print_usage(COMMAND_GRADUATE, USAGE_GRADUATE, false);
    this->print_usage(COMMAND_INTERRUPT, USAGE_INTERRUPT, false);
    this->print_usage(COMMAND_RESUME, USAGE_RESUME, false);
    this->print_usage(COMMAND_PRINT, USAGE_PRINT, false);
    this->print_usage(COMMAND_PRINT_ALL, USAGE_PRINT_ALL, false);
    this->print_usage(COMMAND_ENROLL_IN, USAGE_ENROLL_IN, false);
    this->print_usage(COMMAND_ADD_GRADE, USAGE_ADD_GRADE, false);
    this->print_usage(COMMAND_PROTOCOL, USAGE_PROTOCOL, false);
    this->print_usage(COMMAND_REPORT, USAGE_REPORT, false);
    this->print_usage(COMMAND_OPEN, USAGE_OPEN, false);
    this->print_usage(COMMAND_CLOSE, "", false);
    this->print_usage(COMMAND_SAVE, "", false);
    this->print_usage(COMMAND_SAVE_AS, USAGE_SAVE_AS, false);
    this->print_usage(COMMAND_HELP, "", false);
    this->print_usage(COMMAND_EXIT, "", false);
}

void IOHandler::print_exit() const
{
    std::cout << "Bye! :)" << std::endl;
}
