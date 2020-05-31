#include <fstream>
#include "susi_database.hpp"

Database::Database()
{
    // this->populate_data();
    // this->is_loaded = true;
    // this->save("database.db");
    this->is_loaded = false;
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
        this->majors[1].add_course(&this->courses[i], 1);
    }

    this->majors[1].add_course(&this->courses[6], 1);

    // Add students
    this->add_student(Student(81980, &this->majors[0], 7, "Bilyan"));
    this->add_student(Student(81964, &this->majors[0], 7, "Ivana"));
}

bool Database::save(String filename)
{
    if (!this->is_loaded)
    {
        return false;
    }

    String db_file_path = "db/";
    db_file_path += (filename == "") ? this->file_loaded : filename;
    std::ofstream of_stream(db_file_path.to_c_string(), std::ios::binary | std::ios::trunc);

    if (!of_stream)
    {
        return false;
    }

    //! Save all courses
    const int courses_count = this->courses.get_len();

    if (!of_stream.write((char*)&courses_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < courses_count; ++i)
    {
        if (!this->courses[i].write_to_bin(of_stream))
        {
            return false;
        }
    }

    //! Save all majors
    const int majors_count = this->majors.get_len();

    if (!of_stream.write((char*)&majors_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < majors_count; ++i)
    {
        if (!this->majors[i].get_name().write_to_bin(of_stream))
        {
            return false;
        }

        int major_max_years = this->majors[i].get_max_years();
        if (!of_stream.write((char*)&major_max_years, sizeof(int)))
        {
            return false;
        }

        const Vector<Course*>* courses_for_major = this->majors[i].get_courses();
        for (int j = 0; j < major_max_years; ++j)
        {
            const Vector<Course*> courses_for_year_of_major = courses_for_major[j];
            const int courses_for_year_count = courses_for_year_of_major.get_len();

            if (!of_stream.write((char*)&courses_for_year_count, sizeof(int)))
            {
                return false;
            }

            for (int k = 0; k < courses_for_year_count; ++k)
            {
                if (!courses_for_year_of_major[k]->get_name().write_to_bin(of_stream))
                {
                    return false;
                }
            }
        }
    }

    // Save all students
    const int students_count = this->students.get_len();

    if (!of_stream.write((char*)&students_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < students_count; ++i)
    {
        if (!this->students[i].get_name().write_to_bin(of_stream))
        {
            return false;
        }

        double gpa = this->students[i].get_gpa();
        if (!of_stream.write((char*)&gpa, sizeof(double)))
        {
            return false;
        }

        String major_name = this->students[i].get_major()->get_name();
        if (!major_name.write_to_bin(of_stream))
        {
            return false;
        }

        StudentStatus student_status = this->students[i].get_status();
        if (!of_stream.write((char*)&student_status, sizeof(int)))
        {
            return false;
        }

        int fac_number = this->students[i].get_fac_number();
        if (!of_stream.write((char*)&fac_number, sizeof(int)))
        {
            return false;
        }

        int year = this->students[i].get_year();
        if (!of_stream.write((char*)&year, sizeof(int)))
        {
            return false;
        }

        int group = this->students[i].get_group();
        if (!of_stream.write((char*)&group, sizeof(int)))
        {
            return false;
        }
    }

    return of_stream ? true : false;
}

bool Database::load(String filename)
{
    if (this->is_loaded)
    {
        return false;
    }

    String db_file_path = "db/";
    db_file_path += this->is_loaded ? this->file_loaded : filename;
    std::ifstream if_stream(db_file_path.to_c_string(), std::ios::binary);

    if (!if_stream)
    {
        return false;
    }

    if (if_stream.peek() == EOF)
    {
        this->is_loaded = true;
        return true;
    }

    //! Load all courses
    int courses_count;
    if (!if_stream.read((char*)&courses_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < courses_count; ++i)
    {
        Course course;
        course.read_from_bin(if_stream);
        this->courses.push(course);
    }

    //! Load all majors
    int majors_count;
    if (!if_stream.read((char*)&majors_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < majors_count; ++i)
    {
        String major_name;
        major_name.read_from_bin(if_stream);

        int major_max_years;
        if (!if_stream.read((char*)&major_max_years, sizeof(int)))
        {
            return false;
        }

        Major major(major_name.to_c_string(), major_max_years);

        for (int j = 0; j < major_max_years; ++j)
        {
            int courses_for_year_count;
            if (!if_stream.read((char*)&courses_for_year_count, sizeof(int)))
            {
                return false;
            }

            for (int k = 0; k < courses_for_year_count; ++k)
            {
                String course_name;

                if (!course_name.read_from_bin(if_stream))
                {
                    return false;
                }

                Course* found_course = this->get_courses_by_name(course_name)[0];
                major.add_course(found_course, k + 1);
            }
        }

        this->majors.push(major);
    }

    // Load all students
    int students_count = this->students.get_len();
    if (!if_stream.read((char*)&students_count, sizeof(int)))
    {
        return false;
    }

    for (int i = 0; i < students_count; ++i)
    {
        String student_name;
        if (!student_name.read_from_bin(if_stream))
        {
            return false;
        }

        double gpa;
        if (!if_stream.read((char*)&gpa, sizeof(double)))
        {
            return false;
        }

        String major_name;
        if (!major_name.read_from_bin(if_stream))
        {
            return false;
        }

        Major* major = this->get_majors_by_name(major_name)[0];

        StudentStatus student_status;
        if (!if_stream.read((char*)&student_status, sizeof(int)))
        {
            return false;
        }

        int fac_number;
        if (!if_stream.read((char*)&fac_number, sizeof(int)))
        {
            return false;
        }

        int year;
        if (!if_stream.read((char*)&year, sizeof(int)))
        {
            return false;
        }

        int group;
        if (!if_stream.read((char*)&group, sizeof(int)))
        {
            return false;
        }

        Student student(fac_number, major, group, student_name, year, student_status);
        this->students.push(student);
    }

    this->is_loaded = true;
    this->file_loaded = filename;
    return if_stream ? true : false;
}

void Database::make_empty_file(String filename)
{
    String db_subdir_filename = "db/";
    db_subdir_filename += filename;
    std::ofstream empty_file(db_subdir_filename.to_c_string());
    this->is_loaded = true;
    this->file_loaded = filename;
}

bool Database::close()
{
    if (!this->is_loaded)
    {
        return false;
    }

    this->empty();
    this->is_loaded = false;
    return true;
}

void Database::empty()
{
    this->courses.empty_vector();
    this->majors.empty_vector();
    this->students.empty_vector();
    this->file_loaded = "";
    this->is_loaded = false;
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

Vector<Student*> Database::get_students_by_major_and_year(Major* major, int year) const
{
    Vector<Student*> filtered;

    const int students_len = this->students.get_len();
    for (int i = 0; i < students_len; ++i)
    {
        if (this->students[i].get_major() == major && this->students[i].get_year() == year)
        {
            filtered.push(&this->students[i]);
        }
    }

    return filtered;
}

Vector<Student*> Database::get_students_by_course_and_year(Course* course, int year) const
{
    Vector<Student*> filtered;

    const int students_count = this->students.get_len();

    for (int i = 0; i < students_count; ++i)
    {
        if (this->students[i].get_year() == year && this->students[i].is_enrolled_in_or_has_passed(course))
        {
            filtered.push(&this->students[i]);
        }
    }

    return filtered;
}

Vector<Student*> Database::filter_students_by_major(const Vector<Student*>& list, Major* major) const
{
    const int list_count = list.get_len();

    Vector<Student*> filtered;

    for (int i = 0; i < list_count; ++i)
    {
        if (list[i]->get_major() == major)
        {
            filtered.push(list[i]);
        }
    }

    return filtered;
}

void Database::sort_list_of_students_by_fac_number(Vector<Student*>& list) const
{
    const int list_count = list.get_len();

    // perform insertion sort
    for (int i = 0; i < list_count - 1; ++i)
    {
        int min_index = i;

        for (int j = i + 1; j < list_count; ++j)
        {
            if (list[j]->get_fac_number() < list[min_index]->get_fac_number())
            {
                min_index = j;
            }
        }

        Student* temp = list[i];
        list[i] = list[min_index];
        list[min_index] = temp;
    }
}

bool Database::get_is_loaded()
{
    return this->is_loaded;
}
