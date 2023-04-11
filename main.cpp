#include "vektor.hxx"

#include <iostream>

using namespace vektor;

/// Display vektor's emelents
void display(const Vektor<int>& vek);
/// Quick sort implementation for testing purposes
void qsort(Vektor<int>& vek, int low, int high);
/// Quick sort utility function for partitioning
int partition(Vektor<int>& vek, int low, int high);
/// Another utility function necessary for qsort
void swap(const int index1, const int index2, Vektor<int>& vek);

/// Driver code
int main()
{
    int n = 5;
    Vektor<int> vek(n);
    for (int i = 0; i < vek.size(); ++i)
        vek.set(i, n - i);
    for (int i = 0; i < 20; ++i)
    {
        if (i % 2)
            vek.pushback(i * i);
        else
            vek.pushfront(i * i);
    }
    display(vek);
    qsort(vek, 0, vek.size() - 1);
    display(vek);
}

/// Implementations of utility functions
void display(const Vektor<int>& vek)
{
    for (int i = 0; i < vek.size(); ++i)
        cout << vek.get(i) << " ";
    cout << endl;
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
    int pivot = vek.get(high);
    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (vek.get(j) < pivot)
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
    const int temp = vek.get(index1);
    vek.set(index1, vek.get(index2));
    vek.set(index2, temp);
}