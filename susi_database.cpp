#include "susi_database.hpp"

Database::Database()
{
    this->populate_data();
}

void Database::populate_data()
{
    // Add courses
    this->courses.push(Course("Calc_1", CourseType::mandatory));
    this->courses.push(Course("Discrete_Math", CourseType::mandatory));
    this->courses.push(Course("Algebra_1", CourseType::mandatory));
    this->courses.push(Course("Intro_to_Programming", CourseType::mandatory));
    this->courses.push(Course("Geometry", CourseType::mandatory));
    this->courses.push(Course("Languages_Automata_Computability", CourseType::mandatory));
    this->courses.push(Course("English", CourseType::free_elective));

    // Add majors
    this->majors.push(Major("Computer_Science"));
    this->majors.push(Major("Software_Engineering"));
    this->majors.push(Major("Informatics"));
    this->majors.push(Major("Information_Systems"));

    // Assign courses to majors
    for (int i = 0; i < this->courses.get_len(); ++i)
    {
        this->majors[0].add_course(&this->courses[i], 1);
    }

    this->majors[1].add_course(&this->courses[6], 1);

    // Add students
    this->add_student(Student(81980, &this->majors[0], 7, "Bilyan"));
    this->add_student(Student(81964, &this->majors[0], 7, "Ivana"));
}

void Database::add_student(Student student)
{
    Student* existing_student = this->get_student_by_fac_number(student.get_fac_number());

    if (existing_student != nullptr)
    {
        std::cout << "Database error: student with faculty number already exists";
        return;
    }

    this->students.push(student);
}

Vector<Major*> Database::get_majors_by_name(String name) const
{
    Vector<Major*> filtered;

    const int majors_len = this->majors.get_len();
    for (int i = 0; i < majors_len; ++i)
    {
        if (this->majors[i].get_name() == name)
        {
            filtered.push(&this->majors[i]);
        }
    }

    return filtered;
}

Student* Database::get_student_by_fac_number(int fac_number) const
{
    const int students_len = this->students.get_len();

    for (int i = 0; i < students_len; ++i)
    {
        if (this->students[i].get_fac_number() == fac_number)
        {
            return &this->students[i];
        }
    }

    return nullptr;
}

Vector<Major*> Database::get_majors() const
{
    Vector<Major*> all_majors;

    const int majors_len = this->majors.get_len();
    for (int i = 0; i < majors_len; ++i)
    {
        all_majors.push(&this->majors[i]);
    }

    return all_majors;
}

Vector<Course*> Database::get_courses() const
{
    Vector<Course*> all_courses;

    const int courses_len = this->courses.get_len();
    for (int i = 0; i < courses_len; ++i)
    {
        all_courses.push(&this->courses[i]);
    }

    return all_courses;
}

Vector<Student*> Database::get_students() const
{
    Vector<Student*> all_students;

    const int students_len = this->students.get_len();
    for (int i = 0; i < students_len; ++i)
    {
        all_students.push(&this->students[i]);
    }

    return all_students;
}

Vector<Course*> Database::get_courses_by_name(String name) const
{
    Vector<Course*> filtered;

    const int courses_len = this->courses.get_len();
    for (int i = 0; i < courses_len; ++i)
    {
        if (this->courses[i].get_name() == name)
        {
            filtered.push(&this->courses[i]);
        }
    }

    return filtered;
}
