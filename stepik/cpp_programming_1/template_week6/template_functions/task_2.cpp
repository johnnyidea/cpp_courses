#include <iostream>
#include <cstddef>

//using namespace std;

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T());
    Array(const Array& other);
    ~Array();
    Array& operator=(Array other);
    void swap(Array &other);
    size_t size() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

private:
    size_t size_;
    T *data_;
};

bool less(int a, int b) { return a < b; }

struct Greater { bool operator()(int a, int b) const { return b < a; } };

template <typename T, typename Comp>
const T& minimum(const Array<T>& ar, const Comp& less)
{
    const T* min = &ar[0];
    for (int i = 1, size = ar.size(); i < size; ++i)
    {
        if (less(ar[i], *min))
        {
            min = &ar[i];
        }
    }
    return *min;
}

int main(int argc, char * argv[])
{
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less); // в min должно попасть число 2
    int max = minimum(ints, Greater()); // в max должно попасть число 15

    return 0;
}