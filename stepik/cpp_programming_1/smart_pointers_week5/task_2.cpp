
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

    explicit SharedPtr(Expression *ptr = 0)
        : _ptr(ptr)
        , _counter(0)
    {
        if (ptr)
            _counter = new size_t(1);
    }

    ~SharedPtr()
    {
        if (_counter && --*_counter == 0)
        {
            delete _counter;
            delete _ptr;
        }
    }

    SharedPtr(const SharedPtr & old_ptr)
        : _ptr    (old_ptr._ptr    )
        , _counter(old_ptr._counter)
    {
        if (_counter)
            ++*_counter;
    }

    SharedPtr& operator=(const SharedPtr & assign_ptr)
    {
        if (_ptr == assign_ptr.get())
            return *this;

        if (_ptr != nullptr)
            --*_counter;

        if (assign_ptr.get() != nullptr)
        {
            ++*assign_ptr._counter;
        }

        _ptr = assign_ptr.get();
        _counter = assign_ptr._counter;

        return *this;
    }

    Expression* get() const
    {
        return _ptr;
    }

    void reset(Expression *ptr = 0)
    {
        if (_counter && --*_counter == 0)
        {
            delete _ptr;
            delete _counter;
        }

        _ptr = ptr;

        if (ptr)
            _counter = new size_t(1);
        else
            _counter = 0;
    }

    Expression& operator*() const
    {
        return *_ptr;
    }

    Expression* operator->() const
    {
        return _ptr;
    }

private:

    size_t * _counter;
    Expression *_ptr;
};

//-----------------------------------------------------------------------------
int main(int argc, char * argv[])
{

    {
        Expression * p_tmp = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        SharedPtr p(p_tmp);
        SharedPtr p2;
        SharedPtr p3;

        p2 = p;

        p.reset(p3.get());
    }
    {
        Expression * p_tmp1 = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        Expression * p_tmp2 = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        SharedPtr p2(p_tmp1);
        SharedPtr p3(p2);
        SharedPtr p4(p_tmp2);

        p3 = p4;
    }


    {
        Expression * p_tmp = new  BinaryOperation (new Number(0.0), '*', new Number(0.0));
        SharedPtr p(p_tmp);
    }

    {
        SharedPtr p(NULL);
    }

    {
        Expression *p_tmp4 = new BinaryOperation(new Number(0.0), '*', new Number(0.0));
        SharedPtr p4(p_tmp4);

        p4 = p4;
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
        p5.reset(NULL);
        SharedPtr p6;
        SharedPtr p7;
        p7 = p7;
        p7.reset(NULL);

        SharedPtr p8(new  BinaryOperation (new Number(8.0), '*', new Number(8.0)));
        p8.reset(NULL);
    }
    p1 = p1;





    return 0;
}
