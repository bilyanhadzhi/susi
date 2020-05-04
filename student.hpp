#ifndef STUDENT_HPP
#define STUDENT_HPP

class Student
{
private:

    void copy_from(const Student& other);
    void free_memory();

public:
    Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();
};

#endif // STUDENT_HPP
