#include <iostream>
#include "string.hpp"
#include "io_handler.hpp"

void test();

int main(void)
{
    test();
}

void test()
{
    IOHandler io_handler;

    io_handler.input_command();
    io_handler.input_args(std::cin);

}
