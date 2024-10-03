#include <iostream>
#include "vektor.hxx"

using namespace vektor;


// Display vektor's emelents.
void display(const Vektor<int>& vek);
// Quick sort implementation for testing purposes.
void qsort(Vektor<int>& vek, int low, int high);
// Quick sort utility function for partitioning.
int partition(Vektor<int>& vek, int low, int high);
// Another utility function necessary for qsort.
void swap(const int index1, const int index2, Vektor<int>& vek);

// Driver code.
int main()
{
    // Test no-argument constructor.
    Vektor<int> vek1;
    std::cout << "Test constructor: \t\t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";

    // Test argument constructor.
    int n = 5;
    Vektor<int> vek2(n);
    std::cout << "Test argument constructor: \t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";

    // Test assignment operator.
    vek1 = vek2;
    std::cout << "Test assignment operator: \t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";

    // Fill in the vektor with some data.
    for (int i = 0; i < vek1.size(); ++i)
        vek1[i] = n - i;
    std::cout << "Starting data of the array: ";
    display(vek1);

    // Test copy constructor.
    Vektor<int> vek = vek1;
    std::cout << "Test copy constructor: \t\t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";

    // Fill in the vektor with more data.
    for (int i = 0; i < 20; ++i)
    {
        if (i % 2)
            vek.pushback(i * i);
        else
            vek.pushfront(i * i);
    }

    // Display contents before and after sorting.
    std::cout << "Before sorting:\n";
    display(vek);

    // Test move constructor.
    Vektor<int> vek3(std::move(vek));
    std::cout << "Test move constructor: \t\t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";
    qsort(vek3, 0, vek3.size() - 1);

    // Test move assignment operator.
    vek = std::move(vek3);
    std::cout << "Test move constructor: \t\t PASS\n";
    std::cout << "Instances: " << Vektor<int>::getInstances() << "\n\n";

    // Display contents using non-const iterator.
    std::cout << "After sorting:\n";
    for (Vektor<int>::iterator itr = vek.begin(); itr != vek.end(); ++itr)
        std::cout << *itr << " ";
    std::cout << "\n";
}

// Utilities.
void display(const Vektor<int>& vek)
{
    // Exercise const_iterator, fails with plain iterator.
    Vektor<int>::const_iterator itr = vek.begin();
    Vektor<int>::const_iterator end = vek.end();
    for (itr; itr != end; ++itr)
        std::cout << *itr << " ";
    std::cout << "\n";
}

void qsort(Vektor<int>& vek, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vek, low, high);
        qsort(vek, low, pivot - 1);
        qsort(vek, pivot + 1, high);
    }
}

int partition(Vektor<int>& vek, int low, int high)
{
    int pivot = vek[high];
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (vek[j] < pivot)
        {
            swap(i, j, vek);
            ++i;
        }
    }
    swap(i, high, vek);
    return i;
}

void swap(const int index1, const int index2, Vektor<int>& vek)
{
    const int temp = vek[index1];
    vek[index1] = vek[index2];
    vek[index2] = temp;
}