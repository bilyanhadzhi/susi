#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>

//! String implementation

class String
{
private:
    char* value;
    int len;
    int capacity;
    void copy_from(const String& other);
    void free_memory();
    // Get how much capacity is necessary to store string (min. is 256)
    int get_needed_capacity(const char* string) const;
    // Double the capacity and move string
    void increase_capacity();

public:
    //! Empty-string constructor
    String();
    //! Constructor via const C-string
    String(const char* str);
    //! Copy constructor
    String(const String& other);
    String& operator=(const String& other);
    //! Replace string value with str (frees old value)
    String& operator=(const char* str);
    //! Feed string to output stream (i.e. cout)
    friend std::ostream& operator<<(std::ostream& o_stream, const String& string);
    //! Get string from input stream (i.e. cin)
    friend std::istream& operator>>(std::istream& i_stream, String& string);
    //! Check strings for equality by comparing C strings
    friend bool operator==(const String& left_string, const String& right_string);
    //! Check whether C string matches string value
    friend bool operator==(const String& string, const char* c_string);
    //! Check whether C string matches string value
    friend bool operator==(const char* c_string, const String& string);
    //! Check strings for inequality by comparing C strings
    friend bool operator!=(const String& left_string, const String& right_string);
    //! Check whether C string does not match string value
    friend bool operator!=(const String& string, const char* c_string);
    //! Check whether C string does not match string value
    friend bool operator!=(const char* c_string, const String& string);
    //! Get the i-th character (returns '\0' when i out of bounds; errors when given negative i)
    char operator[](int i) const;
    //! Read into value from binary file
    bool read_from_bin(std::ifstream& if_stream);
    //! Write string to end of binary file, first length then value
    bool write_to_bin(std::ofstream& of_stream) const;
    //! Append character to string
    String& operator+=(const char new_char);
    //! Append string to string
    String& operator+=(const String to_append);
    //! Append c-string to string
    String& operator+=(const char* to_append);
    //! Free dynamic memory allocated by string
    ~String();
    //! Set new value for string and update length (frees old value)
    void set_value(const char* value);
    //! Get from consone until newline (and/or until space, if second argument is true)
    void input(std::istream& i_stream, bool whole_line = false);
    //! Get length of string
    int get_len() const;
    //! Check if string could be converted to a number
    bool is_valid_number(bool check_for_int_only = false) const;
    //! Convert string to number (returns very large negative number for invalid strings)
    double to_double() const;
    //! Same like to_double, cast to int
    int to_int() const;
    //! Get string value as const char*
    const char* to_c_string() const;
};

std::ostream& operator<<(std::ostream& o_stream, const String& string);
std::istream& operator>>(std::istream& i_stream, String& string);

#endif // STRING_HPP
