/// Vector of integers interface 'Vektor', notice 'k'.
/// The idea of this Vektor is to keep user data like this
/// [allocated memory][user's array][allocated memory]
/// The allocated parts memory will be available to users only
/// if they explicitly change vektor's size with either pushback
/// or pushfront methods. This structure will allow us to reduce 
/// the number resizing operations by allocating about 
/// twice as much memory  as users may request.

#pragma once
#ifndef VEKTOR_HPP
#define VEKTOR_HPP

using namespace std;

namespace vektor
{
class Vektor {
public:
    /// Static member function to get the number of Vektor instances currently allocated in the program
    static int getInstances();

    /// No argument constructor allocating a 32-element array
    Vektor();

    /// Constructor with initial number of elements for a newly created vektor
    /// \param size: Initial size of the vektor-array
    Vektor(int size);

    /// Copy constructor
    /// \param &other: Other instance of Vektor class
    Vektor(const Vektor& other);

    /// Assignment operator 
    /// \param &other: Other instance of Vektor class
    Vektor& operator= (const Vektor& other);

    /// Getter of Vektor's length/size available to user
    int size() const;

    /// Getter of a certain element by index
    /// Throws length_error in case of error
    /// \param index: Index of an accessible element
    int get(int index) const;

    /// Set function to assign a certain element a value by its index
    /// Throws length_error in case of error
    /// \param index: Index of an accessible element
    /// \param value: Integer value of a desired element
    void set(int index, int value);

    /// Pushback: adds an element to the end of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushback(int value);
    /// Pushfront: adds an element to the beginning of the array, resizing if necessary
    /// \param value: Integer value of a desired element
    void pushfront(int value);

    /// Destructor deallocating memory of object instances
    ~Vektor();
private:
    /// Static member to display the number of Vektor instances currently allocated
    static int instances;

    /// Resizing method, doubles the size of the current array
    /// and keeps users' data in the middle
    int* resize();

    /// Debugging function displays full contents of the vektor
    /// Can be moved to public to be used in development
    void debug();

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
    int* vektor;
};
}
#endif
