#include <iostream>
#include <cstring>

#include "io_handler.hpp"
#include "constants.hpp"

void IOHandler::free_memory()
{
    this->free_args();
}

void IOHandler::free_args()
{
    if (this->args)
    {
        delete[] this->args;
    }
    this->args = nullptr;
}

void IOHandler::copy_from(const IOHandler& other)
{
    this->command = other.command;
    this->number_of_args = other.number_of_args;
    this->args_capacity = other.args_capacity;
    this->set_args(other.args, other.number_of_args);
}

void IOHandler::set_args(String* args, int number_of_args)
{
    this->args = new String[number_of_args];

    for (int i = 0; i < number_of_args; ++i)
    {
        this->args[i] = args[i];
    }
}

void IOHandler::set_command(const char* command)
{
    this->command = command;
}

IOHandler::IOHandler()
{
    this->args_capacity = IOHANDLER_DEFAULT_ARGS_SIZE;
    this->number_of_args = 0;
    this->args = new String[this->args_capacity];
}

IOHandler::IOHandler(const IOHandler& other)
{
    this->copy_from(other);
}

IOHandler& IOHandler::operator=(const IOHandler& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->free_memory();
    this->copy_from(other);
    return *this;
}

IOHandler::~IOHandler()
{
    this->free_memory();
}

void IOHandler::input_command()
{
    std::cin >> this->command;
    // std::cout << this->command << std::endl;
}

void IOHandler::input_args(std::istream& i_stream)
{
    this->free_args();
    this->args_capacity = IOHANDLER_DEFAULT_ARGS_SIZE;
    this->args = new String[this->args_capacity];

    do
    {
        if (this->number_of_args + 1 >= this->args_capacity)
        {
            this->increase_args_capacity();
        }

        i_stream >> this->args[this->number_of_args++];
    }
    while (i_stream.peek() != '\n');

    // for (int i = 0; i < this->number_of_args; ++i)
    // {
    //     std::cout << this->args[i] << "|";
    // }
    // std::cout << std::endl;
}

void IOHandler::increase_args_capacity()
{
    String* new_args = new String[this->args_capacity * 2];

    for (int i = 0; i < this->args_capacity; ++i)
    {
        new_args[i] = this->args[i];
    }

    this->free_args();
    this->args_capacity *= 2;

    this->args = new_args;
}
