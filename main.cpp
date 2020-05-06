#include <iostream>
#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "io_handler.hpp"

void test_io_handler();
void test_vector();


int main(void)
{
    test_vector();
}

void test_io_handler()
{
    IOHandler io_handler;

    io_handler.input_command();
    io_handler.input_args(std::cin);
}

void test_vector()
{
    Vector<String> vec1;

    vec1.push("abc");

    return;
}
