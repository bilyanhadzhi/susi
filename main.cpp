#include <iostream>
#include "lib/string.hpp"
#include "lib/vector.hpp"
#include "io_handler.hpp"
#include "passed_course.hpp"
#include "student.hpp"
#include "susi.hpp"

void test_io_handler();
void test_vector();
void test_passed_course();
void test_student();
void test_string();
void test_app();

int main(void)
{
    // test_vector();
    test_app();
}

void test_app()
{
    SUSI susi_app;

    susi_app.run();
}

void test_string()
{
    String str;

    return;
}

void test_student()
{
    Student student;

    return;
}

void test_io_handler()
{
    IOHandler io_handler;

    io_handler.input_command();
    io_handler.input_args(std::cin);
}

void test_vector()
{
    Vector<Course*> vec1;
    Course* ptr = new Course("CompSci", CourseType::mandatory);
    Course* ptr2 = new Course("OOP", CourseType::mandatory);
    vec1.push(ptr);
    vec1.push(ptr2);

    std::cout << vec1.get_first_occurrence(ptr2);

    delete ptr, ptr2;
    std::cout << std::endl;

    return;
}

void test_passed_course()
{
    Course algebra("Algebra", CourseType::mandatory);
    PassedCourse passed_course(&algebra, 4);

    return;
}
