#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"

//! A very helpful class responsible for parsing commands and arguments and printing messages for errors/sucesses

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
    void print_usage(String command, String usage = "", bool with_prefix = true) const;
    //! Print error with description
    void print_error(String desc) const;
    //! Print unknown command
    void print_unknown_command() const;
    //! Print success with message
    void print_success(String message) const;
    //! Print help on using the app
    void print_help() const;
    //! Print message for exiting the application
    void print_exit() const;
};

#endif // IO_HANDLER_HPP
