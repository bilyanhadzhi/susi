#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"

class IOHandler
{
private:
    String command;
    Vector<String> args;
    void set_command(String command);
    void clean_args();

public:
    //! Get first string from the console
    void input_command();
    //! Get argument list (works for files, too)
    void input_args(std::istream& i_stream);
    //! Get current command
    String get_command() const;
    //! Get current arguments in a list
    Vector<String> get_args() const;
    //! Returns whether the number of current arguments is 'num_of_args'
    bool check_number_of_arguments(int num_of_args) const;
    //! Print shell prompt
    void print_prompt() const;
    //! Print usage of command
    void print_usage(String command, String usage) const;
    //! Print error with description
    void print_error(String desc) const;
    //! Print unknown command
    void print_unknown_command() const;
    //! Print success with message
    void print_success(String message) const;
};

#endif // IO_HANDLER_HPP
