/// Template vector interface 'Vektor'.
/// The idea of this Vektor is to keep user data like this
/// [allocated memory][user's array][allocated memory]
/// The allocated parts of memory will be available to users only
/// if they explicitly change _vektor's size with either pushback
/// or pushfront methods. This structure will allow us to reduce 
/// the number resizing operations by allocating about 
/// twice as much memory  as users may request.

#pragma once
#ifndef VEKTOR_HXX
#define VEKTOR_HXX

#include <iostream>
#include <stdexcept>

namespace vektor {

template <typename T>
class Vektor {
public:
    /// Static member function to get the number of Vektor instances currently allocated in the program.
    static int getInstances()
    {
        return _instances;
    }

    /// No-argument constructor allocating a 32-element array.
    Vektor() : Vektor(0) {}

    /// Constructor with initial number of elements for a newly created vektor.
    /// \param size: Initial size of the vektor-array.
    explicit Vektor(int size) :
        _length(32), _userLength(size)
    {
        if (size < 0)
            throw std::length_error("Negative size vektor creation attempt.");
        ++_instances;

        // The actual length must always be greater than the user's.
        while (_length < size)
            _length *= 2;

        // This is why we double it once more to make sure that their sizes are not too close.
        // In case initial size is less than 32 but close to 32, or in case of greater sizes.
        if (_length - size < _default_margin || _length > 32)
            _length *= 2;

        // Here we should be somewhere in the middle of the inaccessible to user array.
        _start = (_length - size) / 2;
        _finish = _start + size - 1;

        /// Memory allocation.
        _vektor = new T[_length];
    }

    /// Copy constructor.
    /// \param &other: Other instance of Vektor class.
    Vektor(const Vektor& other) :
        _length(other._length), _userLength(other._userLength), _start(other._start), _finish(other._finish)
    {
        ++_instances;

        // Memory allocation.
        _vektor = new T[_length];
        for (int i = 0; i < _length; ++i)
            _vektor[i] = other._vektor[i];
    }

    /// Assignment operator.
    /// \param &other: Other instance of Vektor class.
    Vektor& operator= (const Vektor& other)
    {
        // If assigning to itself.
        if (this == &other)
            return *this;

        T* newVektor = new T[other._length];

        // Copy existing values.
        for (int i = 0; i < other._length; ++i)
            newVektor[i] = other._vektor[i];

        delete[] _vektor;

        _vektor = newVektor;
        _length = other._length;
        _userLength = other._userLength;
        _start = other._start;
        _finish = other._finish;

        return *this;
    }

    /// Move constructor.
    /// \param &other: Other instance of Vektor class.
    Vektor(Vektor&& other) noexcept :
        _length(other._length), _userLength(other._userLength), _start(other._start), _finish(other._finish), _vektor(other._vektor)
    {
        ++_instances;
        other._length = 0;
        other._userLength = 0;
        other._start = 0;
        other._finish = 0;
        other._vektor = nullptr;
    }

    /// Move assignment operator.
    /// \param &other: Other instance of Vektor class.
    Vektor& operator= (Vektor&& other) noexcept
    {
        if (this != &other)
        {
            delete[] _vektor;

            _length = other._length;
            _userLength = other._userLength;
            _start = other._start;
            _finish = other._finish;
            _vektor = other._vektor;

            other._length = 0;
            other._userLength = 0;
            other._start = 0;
            other._finish = 0;
            other._vektor = nullptr;
        }

        return *this;
    }

    /// Getter of Vektor's length/size available to user.
    int size() const
    {
        return _finish - _start + 1;
    }

    /// Getter of elements by index.
    /// Throws length_error in case of error.
    /// \param index: Index of an accessible element.
    T& operator [](int index)
    {
        if (_userLength == 0 || index < 0 || index + _start > _finish)
            throw std::length_error("Unavailable memory access attempt.");

        return _vektor[_start + index];
    }

    /// Getter of elements by index.
    /// Throws length_error in case of error.
    /// \param index: Index of an accessible element.
    T operator [](int index) const
    {
        if (_userLength == 0 || index < 0 || index + _start > _finish)
            throw std::length_error("Unavailable memory access attempt.");

        return _vektor[_start + index];
    }

    /// Pushback: adds an element to the end of the array, resizing if necessary.
    /// \param value: Value of the desired element.
    void pushback(T value)
    {
        if (_start + _userLength == _length)
            _vektor = _get_doubled_vektor();
        ++_userLength;
        ++_finish;
        _vektor[_finish] = value;
    }

    /// Pushfront: adds an element to the beginning of the array, resizing if necessary.
    /// \param value: Value of the desired element.
    void pushfront(T value)
    {
        if (_start == 0)
            _vektor = _get_doubled_vektor();
        ++_userLength;
        --_start;
        _vektor[_start] = value;
    }

    /// Destructor deallocating memory of object instances.
    ~Vektor()
    {
        --_instances;

        // Memory deallocation.
        delete[] _vektor;
    }

    // Iterators' part is here:
    struct iterator 
    {
        /// Argument constructor.
        iterator(T *arg): _ptr(arg) {}

        /// Dereference operator.
        T& operator *() const { return *_ptr; }
        /// Pointer operator.
        T* operator ->() { return _ptr; };
        /// Prefix increment operator.
        iterator& operator ++() { _ptr++; return *this; }
        /// Suffix increment operator.
        iterator operator ++(int) { iterator temp = *this; ++(*this); return temp; }
        /// Comparison operator.
        friend bool operator ==(const iterator& a, const iterator& b) { return (a._ptr == b._ptr); }
        /// Not equal bool operator.
        friend bool operator !=(const iterator& a, const iterator& b) { return (a._ptr != b._ptr); }

    private:
        T *_ptr;
    };

    iterator begin() { return iterator(&_vektor[_start]); }
    iterator end() { return iterator(&_vektor[_finish + 1]); }

    struct const_iterator
    {
        /// Argument constructor.
        const_iterator(const T* arg) : _ptr(arg) {}

        /// Dereference operator.
        const T& operator *() const { return *_ptr; }
        /// Pointer operator.
        const T* operator ->() { return _ptr; };
        /// Prefix increment operator.
        const const_iterator& operator ++() { _ptr++; return *this; }
        /// Suffix increment operator.
        const const_iterator operator ++(int) { const_iterator temp = *this; ++(*this); return temp; }
        /// Comparison operator.
        friend bool operator ==(const const_iterator& a, const const_iterator& b) { return (a._ptr == b._ptr); }
        /// Not equal bool operator.
        friend bool operator !=(const const_iterator& a, const const_iterator& b) { return (a._ptr != b._ptr); }

    private:
        const T* _ptr;
    };

    const_iterator begin() const { return const_iterator(&_vektor[_start]); }
    const_iterator end() const { return const_iterator(&_vektor[_finish + 1]); }

private:

    /// Static member to display the number of Vektor instances currently allocated.
    static int _instances;

    /// Static constant defining default margin value.
    static constexpr int _default_margin = 16;

    /// Resizing method. Doubles the size of the current array
    /// and keeps users' data in the middle.
    T* _get_doubled_vektor()
    {
        _length *= 2;
        T* newVektor = new T[_length];
        int oldStart = _start;
        int oldFinish = _finish;
        _start = (_length - _userLength) / 2;
        _finish = _start + _userLength - 1;

        // Copy existing values.
        for (int i = 0; i < _userLength; ++i)
            newVektor[_start + i] = _vektor[oldStart + i];

        delete[] _vektor;

        return newVektor;
    }

#ifndef NDEBUG
    /// Debug info for convenience and testing.
    void debug()
    {
        std::cout << "Instances: " << _instances << "\n";
        std::cout << "Full length: " << _length << "\n";
        std::cout << "User length: " << _userLength << "\n";
        std::cout << "Range for user length: [" << _start << " " << _finish << "]" << "\n";
        std::cout << "All values from _vektor: " << "\n";
        for (int i = 0; i < _length; ++i)
            std::cout << _vektor[i] << " ";
        std::cout << "\n";
        std::cout << "All values accessible to user: " << "\n";
        for (int i = _start; i <= _finish; ++i)
            std::cout << _vektor[i] << " ";
        std::cout << "\n";
    }
#endif

    /// Actual complete size of the Vektor.
    int _length;
    /// Lenght of the Vektor available to its user.
    int _userLength;

    // The following two indeces allow us to implement a dynamic floating array in the middle
    // of a larger one, which will reduce the number of resizing operations.
    /// Index of the first accessible element to user.
    int _start;
    /// Index of the last accessible element to user.
    int _finish;
    /// Pointer to dynamically allocate memory whenever necessary, actual Vektor.
    T* _vektor;
};

/// Instances definition.
template <typename T>
int Vektor<T>::_instances = 0;

} /*vektor*/
#endif /*VEKTOR_HXX*/
