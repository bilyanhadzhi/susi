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
    delete[] this->value;
    this->value = nullptr;
}

String::String()
{
    this->capacity = BUFFER_SIZE;
    this->value = new char[this->capacity];
    this->len = 0;
}

String::String(const char* str)
{
    assert(str != nullptr);

    this->capacity = this->get_needed_capacity(str);
    this->value = new char[this->capacity];
    strcpy(this->value, str);
    this->len = strlen(this->value);

}

String::String(const String& other)
{
    this->capacity = other.capacity;
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
    const int value_len = strlen(value);

    this->capacity = this->get_needed_capacity(value);
    this->len = value_len;

    char* new_value = new char[this->capacity];

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

    char* value_new_capacity = new char[this->capacity];
    strcpy(value_new_capacity, this->value);

    delete[] this->value;
    this->value = value_new_capacity;
}

int String::get_needed_capacity(const char* string)
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

std::istream& operator>>(std::istream& i_stream, String& string)
{
    char buf[BUFFER_SIZE];
    i_stream >> buf;

    string.free_memory();
    string.capacity = string.get_needed_capacity(buf);
    string.value = new char[string.capacity];
    strcpy(string.value, buf);
    string.len = strlen(string.value);

    return i_stream;
}

char String::operator[](int i)
{
    assert(i >= 0);

    if (i >= this->len)
    {
        return '\0';
    }

    return this->value[i];
}
