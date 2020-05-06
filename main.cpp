#include <iostream>
#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "io_handler.hpp"
#include "passed_course.hpp"
#include "student.hpp"

void test_io_handler();
void test_vector();
void test_passed_course();
void test_student();

int main(void)
{
    test_student();
}

void test_student()
{
    std::cout << sizeof(Student) << std::endl;
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

void test_passed_course()
{
    Course algebra("Algebra", CourseType::mandatory);
    PassedCourse passed_course(&algebra, 4);

    return;
}
