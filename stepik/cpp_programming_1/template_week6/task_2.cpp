/*
 * В предыдущей версии предполагается, что для типа T определены оператор присваивания и конструктор по умолчанию.
 * При создании шаблонных классов контейнеров (вроде Array и не только) разумно стараться минимизировать требования
 * к типам шаблонных параметров. Поэтому усложним задачу, реализуйте класс Array не полагаясь на то, что для типа T
 * определен оператор присваивания и конструктор по умолчанию. Конструктор копирования у типа T есть.

 *Hints: используйте placement new и явный вызов деструктора (смотрите урок 3.4), чтобы создавать и уничтожать объекты,
 *аллоцировать правильно выровненную память можно с помощью new char[N * sizeof(T)], где N - количество элементов массива.
 */
#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;


template <typename T>
class Array
{
public:
    explicit Array(size_t size, const T& value = T())
            :_size(size)
            ,_data((T*) new char[size * sizeof(T)]) //new T[size])
    {
        for (size_t i = 0; i < size; i++)
            _data[i] = value;
    }

    Array(const Array & array)
            :_size(array._size)
            ,_data((T*) new char[array._size * sizeof(T)])
    {
        for (size_t i = 0; i < _size; i++)
            _data[i] = array._data[i];
    };

    ~Array()
    {
        delete [] (char*) _data;
    }

    Array& operator=(const Array &array)
    {
        if (this != &array)
        {
            delete [] (char*) _data;

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


    //TODO delete
    void prnt()
    {
        for (size_t i = 0; i < _size; ++i)
            cout << *(_data + i);
        cout << endl;
    }

private:
    T    * _data;
    size_t _size;
};


/******************************T E S T *********************/
void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();


int main(int argc, char * argv[])
{
    test0();
    test1();

    return 0;
}


void test0()
{
    cout << endl << "*****Test 0(primitives)**********" << endl;
    {
        cout << endl << "*****CHAR**********" << endl;
        Array<char> ar(size_t(5), '0');
        Array<char> x(size_t(4), '4');
        ar = x;
        ar.prnt();

        Array<char> x2(size_t(6), '6');
        ar = x2;
        ar.prnt();
    }
    cout << endl;
    {
        cout << endl << "*****STRING**********" << endl;
        Array<string> cr(size_t(5), "0");
        Array<string> cx(size_t(4), "4");
        cr = cx;
        cr.prnt();

        Array<string> cx2(size_t(6), "6");
        cx2.prnt();
        cr = cx2;
        cr.prnt();
    }
    cout << endl;
    {
        cout << endl << "*****INT**********" << endl;
        Array<int> ir(size_t(5), 0);
        Array<int> ix(size_t(4), 4);
        ir = ix;
        ir.prnt();

        Array<int> ix2(size_t(6), 6);
        ir = ix2;
        ir.prnt();
    }
    cout << endl;
    {
        cout << endl << "*****DOUBLE**********" << endl;
        Array<double> dr(size_t(5), 0.0);
        Array<double> dx(size_t(4), 4.0);
        dr = dx;
        dx.prnt();

        Array<double> ix2(size_t(6), 6.0);
        dr = ix2;
        dr.prnt();
    }
    cout << endl;
    return;
}


void test1()
{
    {
        cout << endl << "*****Test 1(assigment)**********" << endl;
        Array<char> ar(size_t(100), '0');
        Array<char> x(size_t(0), '1');
        ar = x;
        ar.prnt();
    }
    {
        cout << "*****STRING**********" << endl;
        Array<string> cr(size_t(100), "Str0");
        Array<string> cx(size_t(0), "Str1");
        cr = cx;
        cr.prnt();

        Array<string> cx2(size_t(2), "Str3");
        cr = cx2;
        cr.prnt();
    }
    {
        cout << "*****INT**********" << endl;
        Array<int> cr(size_t(100), 0);
        Array<int> cx(size_t(0), 15);
        cr = cx;
        cr.prnt();

        Array<int> cx2(size_t(2), 55);
        cr = cx2;
        cr.prnt();
    }
    return;
}