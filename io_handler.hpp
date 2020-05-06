#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include "lib/string.hpp"

class IOHandler
{
private:
    String command;
    String* args;
    int number_of_args;
    int args_capacity;
    void free_memory();
    void free_args();
    void copy_from(const IOHandler& other);
    // Copy args into this' args
    void set_args(String* args, int number_of_args);
    void set_command(const char* command);
    // Double the arg capacity and move them into new array
    void increase_args_capacity();

public:
    IOHandler();
    IOHandler(const IOHandler& other);
    IOHandler& operator=(const IOHandler& other);
    ~IOHandler();
    //! Get first string from the console
    void input_command();
    //! Get argument list (works for files, too)
    void input_args(std::istream& i_stream);
};

#endif // IO_HANDLER_HPP
