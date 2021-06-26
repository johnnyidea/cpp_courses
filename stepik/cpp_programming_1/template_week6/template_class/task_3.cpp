/*
 * Шаблонные классы можно наследовать. Реализуйте шаблонную структуру ValueHolder с одним типовым параметром T,
 * унаследованную от интерфейса ICloneable. Интерфейс ICloneable содержит всего один виртуальный метод
 * ICloneable* clone() const, который должен вернуть указатель на копию объекта, на котором он был вызван
 * (объект должен быть создан в куче). Шаблон ValueHolder, как говорит его название, хранит всего одно значение
 * (назовите его data_) типа T (для типа T определен конструктор копирования). Не делайте поле data_ закрытым
 * (поэтому в данном случае мы явно пишем, что ValueHolder должна быть структурой).
 */
#include <iostream>
#include <cstddef>


using namespace std;

struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder: public ICloneable// дальше самостоятельно
{
    ValueHolder(const T& data)
        :data_(data)
    {}

    ICloneable * clone() const override
    {
        return new ValueHolder(*this);
    }

    T data_;
};

int main(int argc, char * argv[])
{
    int * x = new int(1);
    ValueHolder value_holder(x);


    return 0;
}