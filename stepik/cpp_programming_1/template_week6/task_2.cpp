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


/*
Класс с закрытым оператором присваивания:
*/
template <typename Tx>
struct X
{
    X()
    {
        this->x_ = new Tx();
        *this->x_ = 1;
    }
    X(const X& inX)
    {
        this->x_ = new Tx();
        *this->x_ = *inX.x_;
    }
    ~X() { delete this->x_; }
    friend std::ostream& operator<< (std::ostream& s, const X& obj)
    {
        s << *(obj.x_);
        return s;
    }
    void set(Tx i)
    {
        *(this->x_) = i;
    }
private:
    X& operator=(const X& inX);
    Tx *x_;
};



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
        ,_data(static_cast<T*>(operator new[] (0* sizeof(T))))
    {
//        _size = 0;
//        _data = nullptr;
    }

    Array(const Array & array)
            :_size(array._size)
            ,_data(static_cast<T*>(operator new[] (array._size * sizeof(T))))
    {
        for (size_t i = 0; i < _size; i++)
            new (_data + i) T(array._data[i]);
    };

    ~Array()
    {
        if (_data)
            delete [] (char*) _data;
    }

    Array& operator=(const Array &array)
    {
        if (this != &array)
        {
            if (_data)
                delete [] (char*) _data;

            _size = array.size();
            _data = static_cast<T*>(operator new[] (array._size * sizeof(T)));
            for (size_t i = 0; i < array.size(); i++)
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

//    Array<Trace> empty1;

    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

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


void test2()
{
    cout << endl << "*****Test 2(copy constructor)**********" << endl;
    {
        cout << "*****CHAR**********" << endl;
        Array<char> x(size_t(3), '3');
        Array<char> ar(x);
        ar.prnt();
    }
    {
        cout << "*****STRING**********" << endl;
        Array<string> x(size_t(3), "333");
        Array<string> ar(x);
        ar.prnt();
    }

    return;
}

void test3()
{
    cout << endl << "*****Test 3(Empty)**********" << endl;
    {
        cout << "*****CHAR**********" << endl;
        Array<char> ar(size_t(0), '0');
        ar = ar;
        ar.prnt();
    }
    {
        cout << "*****STRING**********" << endl;
        Array<string> ar(size_t(0), "0");
        ar = ar;
        ar.prnt();
    }
    return;
}

void test4()
{
    cout << endl << "*****Test 4(assigment A=A) **********" << endl;
    {
        Array<char> ar(size_t(4), '0');
        ar = ar;
        ar.prnt();
    }
    return;
}
void test5()
{
    cout << endl << "*****Test 5(out bound)**********" << endl;
    {
        cout << "*****more**********" << endl;
        Array<char> ar(size_t(4), '0');
//        cout << ar[10] << endl;
    }
    {
        cout << "*****less**********" << endl;
        Array<char> ar(size_t(4), '0');
//        cout << ar[-10] << endl;
    }
    return;
}

void test6()
{
    cout << endl << "*****Test 6(pointer)**********" << endl;
    {
        cout << "*****CHAR(copy)**********" << endl;
        Array<char> *ar = new Array<char>(size_t(4), '4');
        ar->prnt();
        delete ar;
    }
    {
        cout << "*****CHAR(=)**********" << endl;
        Array<char> *ar = new Array<char>(size_t(5), '5');
        ar->prnt();
        Array<char> *xr = ar;
        xr->prnt();
        delete ar;
    }
    return;
}

void test7()
{
    cout << endl << "*****Test 7(X-object)**********" << endl;
    {
        cout << "***** X<INT> **********" << endl;
        X<int> x;
        x.set(4);
        Array<X<int>> *ar = new Array<X<int>>(size_t(4), x);
        ar->prnt();
        delete ar;
    }
    {
        cout << "***** X<CHAR> (new, =, copy) **********" << endl;
        X<char> x;
        x.set('c');
        Array<X<char>> *ar = new Array<X<char>>(size_t(4), x);
        ar->prnt();
        Array<X<char>> *xr = ar;
        xr->prnt();
        Array<X<char>> y(*xr);
        y.prnt();
        delete ar;
    }
    {
        cout << "***** X<STRING> (new, =, copy)**********" << endl;
        X<string> x;
        x.set("There are no tests for this task");
        Array<X<string>> *ar = new Array<X<string>>(size_t(1),x );
        ar->prnt();
        Array<X<string>> *xr = ar;
        xr->prnt();
        Array<X<string>> y(*xr);
        y.prnt();
        delete ar;
    }
    return;
}