#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>

class String
{
private:
    char* value;
    int len;
    int capacity;
    void copy_from(const String& other);
    void free_memory();
    // Get how much capacity is necessary to store string
    int get_needed_capacity(const char* string);
    // Double the capacity and move string
    void increase_capacity();

public:
    String();
    String(const char* str);
    String(const String& other);
    String& operator=(const String& other);
    //! Replace string value with str (frees old value)
    String& operator=(const char* str);
    //! Feed string to output stream (i.e. cout)
    friend std::ostream& operator<<(std::ostream& o_stream, const String& string);
    //! Get string from ionput stream (i.e. cin)
    friend std::istream& operator>>(std::istream& i_stream, String& string);
    //! Get the i-th character (returns null char when i out of bounds; errors when given negative i)
    char operator[](int i);
    ~String();
    //! Set new value for string and update length (frees old value)
    void set_value(const char* value);
};

std::ostream& operator<<(std::ostream& o_stream, const String& string);
std::istream& operator>>(std::istream& i_stream, String& string);

#endif // STRING_HPP
