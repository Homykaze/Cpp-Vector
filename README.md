# Implemented my own version of an STL class 'vector'
After getting to know the mere basics of the Standard Template Library in C++, and the main principles of object-oriented programming, I decided to implement my own version of the 'vector' class called 'Vektor'. It is limited to store only integers, but it is capable to output the size of a vector, set values at an index of an instance of the class, add them to the front and the end of the list, allocating memory quite efficiently other than on each call to these methods.<br>

Furthermore, 3 constructors are implemented for this data structure, such as: a no-argument constructor, constructor with an argument to set the size of a 'Vektor', and a copy constructor, to be able to instantiate a new object upon copying another instance. An assignment operator is implemented to prevent from freeing the same memory more than once to avoid crashes. A destructor is implemented to deallocate memory whenever an instance of this class is out of the scope (or is deleted) of the running instance.

The "efficient" way of memory allocation is in the way the data structure is implemented: the user of the array has access only to the middle part of the structure demonstrated below. An instance of the class allocates twice as much memory whenever necessary.

### [allocated memory][user's array][allocated memory]

Users do not have direct access to the "allocated memory" parts of the data structure, but they can get it upon an explicit request, for example, with a `push_back()` method or similar. The only free access that they have is to the "user's array" section of the structure.
