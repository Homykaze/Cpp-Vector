#include <iostream>

using namespace std;

class vectorOfInt
{
public:
    //No argument constructor
    vectorOfInt();
    //Initial size constructor
    vectorOfInt(int elements);
    //Copy constructor
    vectorOfInt(vectorOfInt &other);
    //Assignment operator
    vectorOfInt& operator= (vectorOfInt& other);
    //Get method to see value at an index
    int get(int index);
    //Get size of the vector
    int size();
    //Set method to change value at an index
    void set(int index, int value);
    //Adds an element at the end of the vector, resizing if necessary
    void pushback(int value);
    //Adds an element to the beginning of the vector, resizing if necessary
    void pushfront(int value);
    //Resizing is happening here
    void resize(int new_size);
    //Destructor
    ~vectorOfInt();

private:
    //Array or vector storing user's data
    int* arr;
    //Size of the vector available for the user
    int sized;
    //Actual size of the vector
    int actual_size;
    //Offsets values by n values forward, utility function
    void offset();
};


int main()
{
    vectorOfInt a(10);
    for (int i = 0; i < a.size(); i++)
    {
        int input;
        cin >> input;
        a.set(i, input);
    }
    for (int i = 0; i < a.size(); i++)
        cout << a.get(i) << " ";
    cout << endl;
    for (int i = 0; i < a.size() - 1; i++)
    {
        for (int j = i + 1; j < a.size(); j++)
        {
            if (a.get(j) < a.get(i))
            {
                int temp = a.get(j);
                a.set(j, a.get(i));
                a.set(i, temp);
            }
        }
    }
    for (int i = 0; i < a.size(); i++)
        cout << a.get(i) << " ";
    cout << endl;
}

//Fine
vectorOfInt::vectorOfInt()
    : sized(32), actual_size(32)
{
    arr = new int[actual_size];
    for (int i = 0; i < actual_size; i++)
        arr[i] = 0;
}
//Fine
vectorOfInt::vectorOfInt(int elements)
    : sized(elements)
{
    actual_size = 2;
    while (actual_size <= sized)
        actual_size *= 2;
    if (sized < 0)
        sized = 0;
    arr = new int[actual_size];
    for (int i = 0; i < actual_size; i++)
        arr[i] = 0;
}
//Fine
int vectorOfInt::get(int index)
{
    if (index < 0 || index >= size())
        return -2123456789;
    return arr[index];
}
//Fine
int vectorOfInt::size()
{
    return sized;
}
//Fine
void vectorOfInt::set(int index, int value)
{
    if (index < 0 || index >= size())
        return;
    arr[index] = value;
}
//Fine
void vectorOfInt::pushback(int value)
{
    if (actual_size == sized)
    {
        actual_size *= 2;
        resize(actual_size);
    }
    arr[sized] = value;
    sized++;
}
//Fine
void vectorOfInt::pushfront(int value)
{
    if (actual_size == sized)
    {
        actual_size *= 2;
        resize(actual_size);
    }
    sized++;
    offset();
    arr[0] = value;
}
//Fine
void vectorOfInt::resize(int new_size)
{
    int *copy = new int[sized];
    for (int i = 0; i < sized; i++)
        copy[i] = arr[i];
    delete arr;
    arr = new int[new_size];
    for (int i = 0; i < new_size; i++)
    {
        if (i < sized)
            arr[i] = copy[i];
        else
            arr[i] = 0;
    }
    delete[] copy;
}
//Fine
void vectorOfInt::offset()
{
    int temp = arr[0];
    for (int i = 1; i < sized; i++)
    {
        int current = arr[i];
        arr[i] = temp;
        temp = current;
    }
}
//Fine
vectorOfInt::~vectorOfInt()
{
    delete[] arr;
}
//Fine
vectorOfInt& vectorOfInt::operator= (vectorOfInt& other)
{
    sized = other.size();
    actual_size = 2;
    while (actual_size <= sized)
        actual_size *= 2;
    delete[] arr;
    arr = new int[actual_size];
    for (int i = 0; i < actual_size; i++)
    {
        if (i < sized)
            arr[i] = other.get(i);
        else
            arr[i] = 0;
    }
    return *this;
}
//Fine
vectorOfInt::vectorOfInt(vectorOfInt& other)
{
    sized = other.size();
    actual_size = 2;
    while (actual_size <= sized)
        actual_size *= 2;
    if (sized < 0)
        sized = 0;
    arr = new int[actual_size];
    for (int i = 0; i < actual_size; i++)
    {
        if (i < sized)
            arr[i] = other.get(i);
        else
            arr[i] = 0;
    }
}
