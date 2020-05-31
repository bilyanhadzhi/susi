#include <fstream>
#include <cstring>
#include <cassert>
#include "string.hpp"
#include "../constants.hpp"

void String::copy_from(const String& other)
{
    this->capacity = this->get_needed_capacity(other.value);
    this->set_value(other.value);
    this->len = other.len;
}

void String::free_memory()
{
    if (this->value != nullptr)
    {
        delete[] this->value;
        this->value = nullptr;
    }
}

String::String()
{
    this->capacity = BUFFER_SIZE;
    this->value = new char[this->capacity]();
    this->len = 0;
}

String::String(const char* str)
{
    assert(str != nullptr);

    this->capacity = this->get_needed_capacity(str);
    this->value = new char[this->capacity]();
    strcpy(this->value, str);
    this->len = strlen(this->value);

}

String::String(const String& other)
{
    this->capacity = other.capacity;
    this->value = nullptr;
    this->set_value(other.value);
    this->len = other.len;
}

String& String::operator=(const String& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->free_memory();
    this->copy_from(other);
    return *this;
}

String& String::operator=(const char* str)
{
    assert(str != nullptr);

    this->set_value(str);

    return *this;
}

String::~String()
{
    this->free_memory();
}

void String::set_value(const char* value)
{
    assert(value != nullptr);

    const int value_len = strlen(value);

    this->capacity = this->get_needed_capacity(value);
    this->len = value_len;

    char* new_value = new char[this->capacity]();

    strcpy(new_value, value);

    if (this->value != nullptr)
    {
        delete[] this->value;
    }

    this->value = new_value;
    this->len = strlen(this->value);
}

void String::increase_capacity()
{
    this->capacity *= 2;

    char* value_new_capacity = new char[this->capacity]();
    strcpy(value_new_capacity, this->value);

    delete[] this->value;
    this->value = value_new_capacity;
}

int String::get_needed_capacity(const char* string) const
{
    int temp_capacity = BUFFER_SIZE;
    int str_len = strlen(string);

    if (str_len == 0)
    {
        return temp_capacity;
    }

    while (temp_capacity < str_len)
    {
        temp_capacity *= 2;
    }

    return temp_capacity;
}

std::ostream& operator<<(std::ostream& o_stream, const String& string)
{
    o_stream << string.value;

    return o_stream;
}

char String::operator[](int i) const
{
    assert(i >= 0);

    if (i >= this->len)
    {
        return '\0';
    }

    return this->value[i];
}

void String::input(std::istream& i_stream, bool whole_line)
{
    char curr_char;
    int string_len = 0;
    int string_capacity = BUFFER_SIZE;

    char* new_string_value = new char[string_capacity]();

    if (i_stream.peek() == EOF || i_stream.peek() == '\n')
    {
        delete[] new_string_value;
        this->set_value("");

        if (std::cin.peek() == '\n')
        {
            std::cin.get();
        }

        return;
    }

    // skip whitespace
    while (i_stream.peek() == ' ')
    {
        i_stream.get();
    }

    do
    {
        curr_char = i_stream.get();

        if (!whole_line && curr_char == ' ')
        {
            break;
        }
        if (curr_char == '\n' || curr_char == EOF)
        {
            break;
        }

        if (string_len + 1 >= string_capacity)
        {
            char* bigger = new char[string_capacity *= 2]();
            strcpy(bigger, new_string_value);

            delete[] new_string_value;
            new_string_value = bigger;
        }

        new_string_value[string_len++] = curr_char;
    } while (i_stream.peek() != '\n');

    new_string_value[string_len] = '\0';
    this->set_value(new_string_value);
    delete[] new_string_value;
}

std::istream& operator>>(std::istream& i_stream, String& string)
{
    string.input(i_stream);

    return i_stream;
}

bool operator==(const String& left_string, const String& right_string)
{
    return strcmp(left_string.value, right_string.value) == 0;
}

bool operator==(const String& string, const char* c_string)
{
    return strcmp(string.value, c_string) == 0;
}

bool operator==(const char* c_string, const String& string)
{
    return strcmp(c_string, string.value) == 0;
}

bool operator!=(const String& left_string, const String& right_string)
{
    return !(left_string == right_string);
}

bool operator!=(const String& string, const char* c_string)
{
    return !(string == c_string);
}

bool operator!=(const char* c_string, const String& string)
{
    return !(c_string == string);
}

String& String::operator+=(const char new_char)
{
    if (this->len + 1 >= this->capacity)
    {
        this->increase_capacity();
    }

    this->value[len] = new_char;

    if (new_char != '\0')
    {
        ++len;
    }

    return *this;
}

String& String::operator+=(const char* to_append)
{
    assert(to_append != nullptr);

    const int to_append_len = strlen(to_append);
    if (to_append_len < 1)
    {
        return *this;
    }

    for (int i = 0; i < to_append_len; ++i)
    {
        *this += to_append[i];
    }

    return *this;
}

String& String::operator+=(const String to_append)
{
    const int to_append_len = to_append.get_len();
    if (to_append_len < 1)
    {
        return *this;
    }

    for (int i = 0; i < to_append_len; ++i)
    {
        *this += to_append[i];
    }

    return *this;
}

int String::get_len() const
{
    return this->len;
}

bool String::is_valid_number(bool check_for_int_only) const
{
    const int len = this->get_len();

    bool found_dot = this->value[0] == '.';
    bool is_valid = true;

    if (len < 1)
    {
        is_valid = false;
    }
    if (this->value[0] != '-' && this->value[0] != '+' && !isdigit(this->value[0]))
    {
        is_valid = false;
    }

    int beg_index = this->value[0] == '-' || this->value[0] == '+';

    for (int i = beg_index; i < len && is_valid; ++i)
    {
        if (!isdigit(this->value[i]))
        {
            if (this->value[i] == '.')
            {
                // Found 2nd dot -> invalid
                if (found_dot)
                {
                    is_valid = false;
                }
                else
                {
                    found_dot = true;
                }
            }
            else
            {
                is_valid = false;
            }
        }
    }

    if (check_for_int_only && found_dot)
    {
        is_valid = false;
    }

    return is_valid;
}

double String::to_double() const
{
    if (!this->is_valid_number())
    {
        return -__DBL_MAX__;
    }

    double result = 0.0;

    int len = this->get_len();
    bool has_sign = this->value[0] == '+' || this->value[0] == '-';
    bool is_int = true;

    int begin_index = has_sign ? 1 : 0;
    int i = begin_index;

    // skip beginning zeros
    while (this->value[i] == '0')
    {
        ++i;
    }

    // get integer part
    while (i < len)
    {
        if (this->value[i] == '.')
        {
            is_int = false;
            ++i;
            break;
        }

        result *= 10;
        result += (int)(this->value[i] - '0');

        ++i;
    }

    // get fractional part
    double divide_by = 10;

    // know decimal places so to round number
    int dec_places = 0;

    if (!is_int)
    {
        while (i < len && dec_places < 2)
        {
            result += (double)(this->value[i] - '0') / divide_by;

            divide_by *= 10;
            ++dec_places;
            ++i;
        }
    }

    if (dec_places >= 2 && (int)(this->value[i] - '0') >= 5)
    {
        result += 10 / divide_by;
    }

    bool is_negative = has_sign && this->value[0] == '-';

    return is_negative ? -result : result;
}

int String::to_int() const
{
    return (int)this->to_double();
}

bool String::read_from_bin(std::ifstream& if_stream)
{
    if (if_stream.eof())
    {
        return false;
    }

    int value_len;
    if (!if_stream.read((char*)&value_len, sizeof(int)))
    {
        return false;
    }

    char* new_value = new char[value_len + 1];

    if (!if_stream.read(new_value, value_len))
    {
        delete[] new_value;
        return false;
    }

    new_value[value_len] = '\0';

    this->set_value(new_value);

    delete[] new_value;
    return true;

}

bool String::write_to_bin(std::ofstream& of_stream) const
{
    if (this->len < 1)
    {
        return false;
    }

    if (!of_stream.write((char*)&this->len, sizeof(int)))
    {
        return false;
    }

    if (!of_stream.write(this->value, this->len))
    {
        return false;
    }

    return true;

}

const char* String::to_c_string() const
{
    return this->value;
}
