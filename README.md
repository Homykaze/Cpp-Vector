# Implemented my own version of an STL class 'vector'
After getting to know the mere basics of the Standard Template Library in C++, and the main principles of object-oriented programming, I implemented my own versions of the 'vector' class called 'Vektor'. This repository contains two versions, one which is limited to store only integers, and a template class, both of which are capable to output the size of a vector, set values at an index of an instance of the class, add them to the front and end of the list relatively efficiently without necessarily resizing the data structure on each call to these methods.<br>

Furthermore, there are 3 constructors implemented for this data structure, such as: a no-argument constructor, constructor with an argument to set the size of a 'Vektor', and a copy constructor, to be able to instantiate a new object upon copying another instance. An assignment operator is implemented to prevent from freeing the same memory more than once to avoid crashes. A destructor is implemented to deallocate memory whenever an instance of this class is out of the scope (or is deleted) of the running instance.<br>

`vektor.hpp` and `vektor.cpp` contain an integer implementation of the class, which was my initial idea for this project.
`vektor.hxx` contains a template implementation of the vector interface, completing this project.
`main.cpp` uses the template implementation from `.hxx` header file, which works for any custom type, this example uses integers for simplicity.
