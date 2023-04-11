#include <iostream>
#include "vektor.hpp"

namespace vektor{

/// Instances declaration
int Vektor::instances = 0;

/// Get number of allocated vektors
int Vektor::getInstances()
{
    return instances;
}

/// No-argument constructor
Vektor::Vektor()
{
    ++instances;
    length = 32;
    userLength = 0;
    begin = 0;
    end = 0;
    /// Memory allocation
    vektor = new int[length];
    /// Initializing data for consistency
    for (int i = 0; i < length; ++i)
        vektor[i] = 0;
}

/// Parameterized constructor
Vektor::Vektor(int size)
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
    vektor = new int[length];
    /// Initializing data for consistency
    for (int i = 0; i < length; ++i)
        vektor[i] = 0;
}

/// Assignment operator
Vektor& Vektor::operator= (const Vektor& other)
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
    vektor = new int[length];
    for (int i = 0; i < length; ++i)
        vektor[i] = other.vektor[i];
    return *this;
}

/// Copy constructor
Vektor::Vektor(const Vektor& other)
{
    length = other.length;
    userLength = other.userLength;
    begin = other.begin;
    end = other.end;
    vektor = new int[length];
    for (int i = 0; i < length; ++i)
        vektor[i] = other.vektor[i];
}

/// Element getter
int Vektor::get(int index) const
{
    if (userLength == 0 || index + begin > end)
        throw length_error("Unavailable memory access attempt.");
    return vektor[begin + index];
}

/// Element setter
void Vektor::set(int index, int value)
{
    if (userLength == 0 || index + begin > end)
        throw length_error("Unavailable memory access attempt.");
    vektor[begin + index] = value;
}

/// Add element to the end of the vektor
void Vektor::pushback(int value)
{

    if (begin + userLength == length)
        vektor = resize();
    ++userLength;
    ++end;
    vektor[end] = value;
}

/// Add element to the beginning of the vektor
void Vektor::pushfront(int value)
{
    if (begin == 0)
        vektor = resize();
    ++userLength;
    --begin;
    vektor[begin] = value;
}

/// Get size of vektor
int Vektor::size() const
{
    return end - begin + 1;
}

/// Resize and rearrange vektor
int* Vektor::resize()
{
    length *= 2;
    int* newVektor = new int[length];
    int oldBegin = begin;
    int oldEnd = end;
    begin = (length - userLength) / 2;
    end = begin + userLength - 1;

    /// Initializing data for consistency
    for (int i = 0; i < length; ++i)
        newVektor[i] = 0;
    /// And copying existing values
    for (int i = 0; i < userLength; ++i)
        newVektor[begin + i] = vektor[oldBegin + i];

    delete[] vektor;
    return newVektor;
}

/// Display all data fields from the class
void Vektor::debug()
{
    cout << "Instances: " << instances << endl;
    cout << "Full length: " << length << endl;
    cout << "User length: " << userLength << endl;
    cout << "Range for user length: [" << begin << " " << end << "]" << endl;
    cout << "All values from vektor: " << endl;
    for (int i = 0; i < length; ++i)
        cout << vektor[i] << " ";
    cout << endl;
    cout << "All values accessible to user: " << endl;
    for (int i = begin; i <= end; ++i)
        cout << vektor[i] << " ";
    cout << endl;
}

/// Destructor
Vektor::~Vektor()
{
    --instances;
    /// Memory deallocation
    delete[] vektor;
}
} /*vektor*/