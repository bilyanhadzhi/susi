#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../constants.hpp"
#include <cassert>

template<typename T>
class Vector
{
private:
    // An array of pointers to T, all 'empty' slots will be nullptr by default
    T** elements;
    int elements_count;
    int elements_capacity;
    void copy_from(const Vector<T>& other);
    void free_memory();
    void increase_capacity();
    void init_vector();

public:
    Vector();
    Vector(const Vector& other);
    Vector<T>& operator=(const Vector& other);
    ~Vector();
    //! Restore vector to initial state
    void empty_vector();
    //! Add element at the end of the vector
    void push(T value);
    //! Get the (semantical) length of the vector
    int get_len() const;
    //! Get value of element at i-th index
    T& operator[](int i) const;
    //! Return index of first occurrence
    int get_first_occurrence(T elem) const;
};

template<typename T>
void Vector<T>::free_memory()
{
    for (int i = 0; i < this->elements_capacity; ++i)
    {
        delete this->elements[i];
    }

    delete[] this->elements;
    this->elements = nullptr;
}

template<typename T>
void Vector<T>::copy_from(const Vector<T>& other)
{
    T** new_elements = new T*[other.elements_capacity];
    for (int i = 0; i < other.elements_count; ++i)
    {
        new_elements[i] = new T(*(other.elements[i]));
    }

    this->elements_capacity = other.elements_capacity;
    this->elements_count = other.elements_count;
    this->elements = new_elements;
}

template<typename T>
Vector<T>::Vector()
{
    this->init_vector();
}

template<typename T>
void Vector<T>::init_vector()
{
    this->elements_capacity = VECTOR_DEFAULT_CAPACITY;
    this->elements = new T*[this->elements_capacity];

    for (int i = 0; i < this->elements_capacity; ++i)
    {
        this->elements[i] = nullptr;
    }

    this->elements_count = 0;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
    this->copy_from(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->free_memory();
    this->copy_from(other);

    return *this;
}

template<typename T>
Vector<T>::~Vector()
{
    this->free_memory();
}

template<typename T>
void Vector<T>::increase_capacity()
{
    T** new_elements = new T*[this->elements_capacity * 2];
    for (int i = 0; i < this->elements_count; ++i)
    {
        new_elements[i] = new T(*(this->elements[i]));
    }

    this->free_memory();
    this->elements_capacity *= 2;
    this->elements = new_elements;
}

template<typename T>
void Vector<T>::push(T value)
{
    if (this->elements_count + 1 >= this->elements_capacity)
    {
        this->increase_capacity();
    }

    this->elements[this->elements_count++] = new T(value);
}

template<typename T>
int Vector<T>::get_len() const
{
    return this->elements_count;
}

template<typename T>
T& Vector<T>::operator[](int i) const
{
    assert(i >= 0);
    assert(i < this->elements_count);

    return *(this->elements[i]);
}

template<typename T>
void Vector<T>::empty_vector()
{
    this->free_memory();
    this->init_vector();
}

template<typename T>
int Vector<T>::get_first_occurrence(T elem) const
{
    for (int i = 0; i < this->elements_count; ++i)
    {
        if (this->elements[i] == elem)
        {
            return i;
        }
    }

    return -1;
}

#endif // VECTOR_HPP
