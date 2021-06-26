/*
 * Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array,
 * приведен в шаблоне кода.
 */
#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;


template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T())
        :_size(size)
        ,_data(new T[size])
    {
        for (size_t i = 0; i < size; i++)
            _data[i] = value;
    }

    Array(const Array & array)
        :_size(array._size)
        ,_data(new T[array._size])
    {
        for (size_t i = 0; i < _size; i++)
            _data[i] = array._data[i];
    };

    ~Array()
    {
        delete [] _data;
    }

    Array& operator=(const Array &array)
    {
        if (this != &array)
        {
            delete [] _data;
            _size = array.size();
            _data = new T[array.size()];
            for (size_t i = 0; i < array.size(); i++)
                _data[i] = array._data[i];
        }
        return *this;
    }

    size_t size() const
    {
        return _size;
    }

    T& operator[](size_t index)
    {
        return _data[index];
    }

    const T& operator[](size_t index) const
    {
        return _data[index];
    }

private:
    T    * _data;
    size_t _size;
};


int main(int argc, char * argv[])
{
    int vals[3] = {1, 2, 3};

    Array<int> array1(3, *vals);
    cout << array1[1] << endl;

    Array<int> array2(array1);

    cout << array2[1] << endl;

    cout << array2.size() << endl;
    {
        Array<int> array3;
        array3 = array2;
    }
    array2 = array2;

    return 0;
}
