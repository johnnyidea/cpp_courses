#include <iostream>
#include <cstddef>

#include <iostream>
#include <sstream>


template <typename T>
class Array
{
public:
    explicit Array(size_t size, const T& value = T())
            :_size(size)
            ,_data(static_cast<T*>(operator new[] (size * sizeof(T))))
    {
        for (size_t i = 0; i < size; i++)
            new (_data + i) T(value);
    }

    Array()
            :_size(0)
            ,_data(static_cast<T*>(operator new[] (0)))
    {}

    Array(const Array & array)
            :_size(array._size)
            ,_data(static_cast<T*>(operator new[] (array._size * sizeof(T))))
    {
        for (size_t i = 0; i < _size; i++)
            new(_data + i)T(array._data[i]);
    };

    ~Array()
    {
        if (_data)
        {
            for (size_t i = 0; i < _size; i++)
                _data[i].~T();

            delete[] (char *) _data;

            _data = nullptr;
        }
    }

    Array& operator=(const Array &array)
    {
        if (this != &array)
        {
            if (_data)
            {
                for (size_t i = 0; i < _size; i++)
                    _data[i].~T();

                delete[] (char *) _data;

                _data = nullptr;
            }

            _size = array.size();
            _data = static_cast<T*>(operator new[] (array.size() * sizeof(T)));
            for (size_t i = 0; i < array._size; i++)
                new (_data + i) T(array._data[i]);
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
    size_t _size;
    T * _data;
};
// Весь вывод должен осуществляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогательные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

template <typename T>
void flatten(const T& el, std::ostream& out)
{
        std::ostringstream oss;
        oss << el;
        out << oss.str().c_str() << " ";
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{
    for (size_t i = 0; i < array.size(); i++)
    {
        flatten(array[i], out);
//        std::ostringstream oss;
//        oss << array[i];
//        out << oss.str().c_str() << " ";
    }
}

int main(int argc, char * argv[])
{
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    flatten(ints, std::cout); // выводит на экран строку "10 20"

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
//
//    Array<double> doubles(10, 0.0);
//    flatten(doubles, std::cout); // работать должно не только для типа int

    return 0;
}