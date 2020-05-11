#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include "lib/string.hpp"
#include "lib/vector.hpp"

class IOHandler
{
private:
    String command;
    Vector<String> args;
    void set_command(const char* command);
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
    //! Get argument at index i
    String get_arg_at(int i) const;
};

#endif // IO_HANDLER_HPP
