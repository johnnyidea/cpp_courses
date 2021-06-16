
/*
 * Помните иерархию Expression, которую мы разрабатывали на четвёртой неделе? Реализуйте ScopedPtr, который будет
 * работать с указателями на базовый класс Expression. В этом задании вам требуется реализовать методы get, release
 * и reset, операторы * и -> так, как это было описано в предыдущем степе. А также реализуйте конструктор ScopedPtr
 * от указателя на Expression.

Подсказка: в качестве признака того, что ScopedPtr не хранит никакого указателя (после вызова release), используйте
нулевой указатель, при этом вы можете явно проверить указатель в деструкторе, но делать это не обязательно, так как
delete от нулевого указателя ничего не делает.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно.
 */

//-----------------------------------------------------------------------------

#include <iostream>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------


struct Expression
{
    virtual double evaluate() const = 0;

    virtual ~Expression(){}
};

struct Number : Expression
{
    Number(double value)
            : value(value)
    {}

    double evaluate() const
    {
        return value;
    }

private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const * left, char op, Expression const * right)
            : left(left), op(op), right(right)
    {}

    double evaluate() const
    {
        if (op == '+')
            return left->evaluate() + right->evaluate();

        if (op == '*')
            return left->evaluate() * right->evaluate();

        if (op == '/')
            return left->evaluate() / right->evaluate();

        if (op == '-')
            return left->evaluate() - right->evaluate();
    }

    ~BinaryOperation(){
        delete left;
        delete right;
    };

private:
    Expression const * left;
    Expression const * right;
    char op;
};

//-----------------------------------------------------------------------------

struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    explicit ScopedPtr(Expression *ptr = 0)
    {
        ptr_ = ptr;
    }

    ~ScopedPtr()
    {
        delete ptr_;
    }

    Expression* get() const
    {
        return ptr_;
    }

    Expression* release()
    {
        Expression * new_ptr = ptr_;
        ptr_ = 0;
        return std::move(new_ptr);
    }

    void reset(Expression *ptr = 0)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};


//-----------------------------------------------------------------------------
int main(int argc, char * argv[])
{
    // сначала создаём объекты для подвыражения 4.5 * 5
    Expression * sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
    // потом используем его в выражении для +
    Expression * expr = new BinaryOperation(new Number(3), '*', sube);


    ScopedPtr scoped_ptr(expr);

    // вывоз метода расчета результата через оператор "стрелочка"
    std::cout << scoped_ptr->evaluate() << std::endl;

    // вывоз метода расчета результата через оператор разыменования "звездочка"
    std::cout << scoped_ptr.operator*().evaluate() << std::endl;

    // вывоз метода расчета результата через метод get
    std::cout << scoped_ptr.get()->evaluate() << std::endl;

    auto tmp = scoped_ptr.release();

    if (scoped_ptr.get() == nullptr)
        cout << "";

    Expression * new_expr = new BinaryOperation(new Number(1.0), '+', new Number(2));
    scoped_ptr.reset(new_expr);

    return 0;
}
