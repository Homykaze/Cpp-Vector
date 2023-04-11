/// Template vector interface 'Vektor', notice 'k'.
/// The idea of this Vektor is to keep user data like this
/// [allocated memory][user's array][allocated memory]
/// The allocated parts of memory will be available to users only
/// if they explicitly change vektor's size with either pushback
/// or pushfront methods. This structure will allow us to reduce 
/// the number resizing operations by allocating about 
/// twice as much memory  as users may request.

#pragma once
#ifndef VEKTOR_HPP
#define VEKTOR_HPP

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
        begin = 0;
        end = 0;
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
        begin = (length - size) / 2;
        end = begin + size - 1;
        /// Memory allocation
        vektor = new T[length];
    }

    /// Copy constructor
    /// \param &other: Other instance of Vektor class
    Vektor(const Vektor& other)
    {
        length = other.length;
        userLength = other.userLength;
        begin = other.begin;
        end = other.end;
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
        begin = other.begin;
        end = other.end;
        delete[] vektor;
        vektor = new T[length];
        for (int i = 0; i < length; ++i)
            vektor[i] = other.vektor[i];
        return *this;
    }

    /// Getter of Vektor's length/size available to user
    int size() const
    {
        return end - begin + 1;
    }

    /// Getter of a certain element by index
    /// Throws length_error in case of error
    /// \param index: Index of an accessible element
    T get(int index) const
    {
        if (userLength == 0 || index + begin > end)
            throw std::length_error("Unavailable memory access attempt.");
        return vektor[begin + index];
    }

    /// Set function to assign a certain element a value by its index
    /// Throws length_error in case of error
    /// \param index: Index of an accessible element
    /// \param value: Integer value of a desired element
    void set(int index, int value)
    {
        if (userLength == 0 || index + begin > end)
            throw std::length_error("Unavailable memory access attempt.");
        vektor[begin + index] = value;
    }

    /// Pushback: adds an element to the end of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushback(T value)
    {
        if (begin + userLength == length)
            vektor = resize();
        ++userLength;
        ++end;
        vektor[end] = value;
    }

    /// Pushfront: adds an element to the beginning of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushfront(T value)
    {
        if (begin == 0)
            vektor = resize();
        ++userLength;
        --begin;
        vektor[begin] = value;
    }

    /// Destructor deallocating memory of object instances
    ~Vektor()
    {
        --instances;
        /// Memory deallocation
        delete[] vektor;
    }

private:

    /// Static member to display the number of Vektor instances currently allocated
    static int instances;

    /// Resizing method, doubles the size of the current array
    /// and keeps users' data in the middle
    T* resize()
    {
        length *= 2;
        T* newVektor = new T[length];
        int oldBegin = begin;
        int oldEnd = end;
        begin = (length - userLength) / 2;
        end = begin + userLength - 1;

        /// Copying existing values
        for (int i = 0; i < userLength; ++i)
            newVektor[begin + i] = vektor[oldBegin + i];

        delete[] vektor;
        return newVektor;
    }

    /// Debugging function displays full contents of the vektor
    /// Can be moved to public to be used in development
    void debug()
    {
        std::cout << "Instances: " << instances << std::endl;
        std::cout << "Full length: " << length << std::endl;
        std::cout << "User length: " << userLength << std::endl;
        std::cout << "Range for user length: [" << begin << " " << std::end << "]" << std::endl;
        std::cout << "All values from vektor: " << std::endl;
        for (int i = 0; i < length; ++i)
            std::cout << vektor[i] << " ";
        std::cout << std::endl;
        std::cout << "All values accessible to user: " << std::endl;
        for (int i = begin; i <= end; ++i)
            std::cout << vektor[i] << " ";
        std::cout << std::endl;
    }

    /// Actual complete size of the Vektor
    int length;
    /// Lenght of the Vektor available to its user
    int userLength;

    /// The following two indeces allow us to implement a dynamic floating array in the middle
    /// of a bigger one, which will significantly reduce the number of resizing operations
    /// Index of the first accessible element to user
    int begin;
    /// Index of the last accessible element to user
    int end;
    /// Pointer to dynamically allocate memory whenever necessary, actual Vektor
    T* vektor;
};

/// Instances definition
template <typename T>
int Vektor<T>::instances = 0;

} /*vektor*/
#endif /*VEKTOR_HPP*/