/// Template vector interface 'Vektor', notice 'k'.
/// The idea of this Vektor is to keep user data like this
/// [allocated memory][user's array][allocated memory]
/// The allocated parts of memory will be available to users only
/// if they explicitly change vektor's size with either pushback
/// or pushfront methods. This structure will allow us to reduce 
/// the number resizing operations by allocating about 
/// twice as much memory  as users may request.

#pragma once
#ifndef VEKTOR_HXX
#define VEKTOR_HXX

#include <iostream>

namespace vektor{

template <typename T>
class Vektor {
public:
    /// Static member function to get the number of Vektor instances currently allocated in the program
    static int getInstances()
    {
        return instances;
    }

    /// No argument constructor allocating a 32-element array
    Vektor()
    {
        ++instances;
        length = 32;
        userLength = 0;
        start = 0;
        finish = 0;
        /// Memory allocation
        vektor = new T[length];
    }

    /// Constructor with initial number of elements for a newly created vektor
    /// \param size: Initial size of the vektor-array
    Vektor(int size)
    {
        ++instances;
        length = 32;
        userLength = size;

        /// The actual length must always be greater than the user's
        while (length < size)
            length *= 2;
        /// This is why we double it once more to make sure that their sizes are not too close
        /// In case initial size is less than 32 but close to 32, or in case of greater sizes
        if (size < length && length - size < 16 || length > 32)
            length *= 2;
        /// Here we should be somewhere in the middle of the inaccessible to user array
        start = (length - size) / 2;
        finish = start + size - 1;
        /// Memory allocation
        vektor = new T[length];
    }

    /// Copy constructor
    /// \param &other: Other instance of Vektor class
    Vektor(const Vektor& other)
    {
        length = other.length;
        userLength = other.userLength;
        start = other.start;
        finish = other.finish;
        vektor = new T[length];
        for (int i = 0; i < length; ++i)
            vektor[i] = other.vektor[i];
    }

    /// Assignment operator 
    /// \param &other: Other instance of Vektor class
    Vektor& operator= (const Vektor& other)
    {
        /// If assigning to itself
        if (this == &other)
            return *this;
        /// Rebuild vektor assigned to from scratch
        length = other.length;
        userLength = other.userLength;
        start = other.start;
        finish = other.finish;
        delete[] vektor;
        vektor = new T[length];
        for (int i = 0; i < length; ++i)
            vektor[i] = other.vektor[i];
        return *this;
    }

    /// Getter of Vektor's length/size available to user
    int size() const
    {
        return finish - start + 1;
    }

    /// Getters of certain elements by index
    /// Throws length_error in case of error
    /// \param index: Index of an accessible element
    T& operator [](int index) {
        if (userLength == 0 || index + start > finish)
            throw std::length_error("Unavailable memory access attempt.");
        return vektor[start + index];
    }

    /// No need for setter methods with these overloaded operators
    T operator [](int index) const {
        if (userLength == 0 || index + start > finish)
            throw std::length_error("Unavailable memory access attempt.");
        return vektor[start + index];
    }

    /// Pushback: adds an element to the end of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushback(T value)
    {
        if (start + userLength == length)
            vektor = resize();
        ++userLength;
        ++finish;
        vektor[finish] = value;
    }

    /// Pushfront: adds an element to the beginning of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushfront(T value)
    {
        if (start == 0)
            vektor = resize();
        ++userLength;
        --start;
        vektor[start] = value;
    }

    /// Destructor deallocating memory of object instances
    ~Vektor()
    {
        --instances;
        /// Memory deallocation
        delete[] vektor;
    }

    /// Iterators' part is here:
    struct iterator 
    {
        /// Argument constructor
        iterator(T *arg): ptr(arg) {}

        /// Dereference operator
        T& operator *() const { return *ptr; }
        /// Pointer operator
        T* operator ->() { return ptr; };
        /// Prefix increment operator
        iterator& operator ++() { ptr++; return *this; }
        /// Suffix increment operator
        iterator operator ++(int) { iterator temp = *this; ++(*this); return temp; }
        /// Comparison operator
        friend bool operator ==(const iterator& a, const iterator& b) { return (a.ptr == b.ptr); }
        /// Not eqial bool operator
        friend bool operator !=(const iterator& a, const iterator& b) { return (a.ptr != b.ptr); }

    private:
        T *ptr;
    };

    iterator begin() { return iterator(&vektor[start]); }
    iterator end() { return iterator(&vektor[finish + 1]); }

    struct const_iterator
    {
        /// Argument constructor
        const_iterator(const T* arg) : ptr(arg) {}

        /// Dereference operator
        const T& operator *() const { return *ptr; }
        /// Pointer operator
        const T* operator ->() { return ptr; };
        /// Prefix increment operator
        const const_iterator& operator ++() { ptr++; return *this; }
        /// Suffix increment operator
        const const_iterator operator ++(int) { const_iterator temp = *this; ++(*this); return temp; }
        /// Comparison operator
        friend bool operator ==(const const_iterator& a, const const_iterator& b) { return (a.ptr == b.ptr); }
        /// Not equal bool operator
        friend bool operator !=(const const_iterator& a, const const_iterator& b) { return (a.ptr != b.ptr); }

    private:
        const T* ptr;
    };

    const_iterator begin() const { return const_iterator(&vektor[start]); }
    const_iterator end() const { return const_iterator(&vektor[finish + 1]); }

private:

    /// Static member to display the number of Vektor instances currently allocated
    static int instances;

    /// Resizing method, doubles the size of the current array
    /// and keeps users' data in the middle
    T* resize()
    {
        length *= 2;
        T* newVektor = new T[length];
        int oldStart = start;
        int oldFinish = finish;
        start = (length - userLength) / 2;
        finish = start + userLength - 1;

        /// Copying existing values
        for (int i = 0; i < userLength; ++i)
            newVektor[start + i] = vektor[oldStart + i];

        delete[] vektor;
        return newVektor;
    }

    /// Debugging function displays full contents of the vektor
    /// Can be moved to public to be used in development
    void debug()
    {
        std::cout << "Instances: " << instances << "\n";
        std::cout << "Full length: " << length << "\n";
        std::cout << "User length: " << userLength << "\n";
        std::cout << "Range for user length: [" << start << " " << "\n" << "]" << "\n";
        std::cout << "All values from vektor: " << "\n";
        for (int i = 0; i < length; ++i)
            std::cout << vektor[i] << " ";
        std::cout << "\n";
        std::cout << "All values accessible to user: " << "\n";
        for (int i = start; i <= finish; ++i)
            std::cout << vektor[i] << " ";
        std::cout << "\n";
    }

    /// Actual complete size of the Vektor
    int length;
    /// Lenght of the Vektor available to its user
    int userLength;

    /// The following two indeces allow us to implement a dynamic floating array in the middle
    /// of a bigger one, which will significantly reduce the number of resizing operations
    /// Index of the first accessible element to user
    int start;
    /// Index of the last accessible element to user
    int finish;
    /// Pointer to dynamically allocate memory whenever necessary, actual Vektor
    T* vektor;
};

/// Instances definition
template <typename T>
int Vektor<T>::instances = 0;

} /*vektor*/
#endif /*VEKTOR_HXX*/