
/*
 *Задание повышенной сложности.
 * Реализуйте класс SharedPtr как описано ранее. Задание немного сложнее, чем кажется на первый взгляд. Уделите особое
 * внимание "граничным случаям" — нулевой указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее.

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

struct SharedPtr
{
    // реализуйте следующие методы
    //
    explicit SharedPtr(Expression *ptr = 0)
            : _ptr(ptr)
            , _counter(1)
    {
//        if (ptr == nullptr)
//            _counter == 0;
    }

    ~SharedPtr()
    {
        if (_counter == 1)
            delete _ptr;

        _counter--;
    }

    SharedPtr(const SharedPtr & old_ptr)
    {
        //NB
        if (old_ptr.get() != nullptr && this != &old_ptr)
        {
            old_ptr
            *this = old_ptr;
        }
    }

    SharedPtr& operator=(const SharedPtr & assign_ptr)
    {
        if (this != &assign_ptr)
        {
            reset(assign_ptr.get());
            _counter = assign_ptr._counter;
        }

        _counter--;

        return *this;
    }

    Expression* get() const
    {
        return _ptr;
    }

    void reset(Expression *ptr = 0)
    {
        if (ptr == nullptr)
        {
            _counter == 1;
        }

        if (_counter == 1)
            delete _ptr;

        _ptr = ptr;
    }

    Expression& operator*() const
    {
        return *_ptr;
    }

    Expression* operator->() const
    {
        return _ptr;
    }

    uint get_counter()
    {
        return _counter;
    }

    void inc()
    {
        ++_counter;
    }
    void dec()
    {
        --_counter;
    }

    private:

    Expression *_ptr;
    uint _counter{0};
};

//-----------------------------------------------------------------------------
int main(int argc, char * argv[])
{
    {
        Expression * p_tmp = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        SharedPtr p(p_tmp);
    }

    {
        SharedPtr p(NULL);
    }

    SharedPtr p1;
    {
        Expression * p_tmp1 = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        Expression * p_tmp2 = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        SharedPtr p2(p_tmp1);
        SharedPtr p3(p_tmp2);
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p3.reset(NULL);
        p3 = p5;
//        p5.reset(NULL);
//        SharedPtr p6;
//        SharedPtr p7;
//        p7 = p7;
//        p7.reset(NULL);
//        p7.reset(new  BinaryOperation (new Number(7.0), '*', new Number(7.0)));
//        SharedPtr p8(new  BinaryOperation (new Number(8.0), '*', new Number(8.0)));
//        p8.reset(NULL);
    }
//    p1 = p1;



    return 0;
}
