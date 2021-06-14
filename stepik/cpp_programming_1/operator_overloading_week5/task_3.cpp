
/*
Задача:
Еще одна важная группа операторов, которые полезно реализовать для класса рациональных чисел — это операторы сравнения.
Реализуйте операторы <, <=, >, >=, ==, != для класса Rational так, чтобы можно было сравнивать объекты класса Rational
не только друг с другом, но и с целыми числами.

При решении задания не используйте метод to_double, он введен в класс, в первую очередь, для удобства тестирования.
Вы можете определять любые вспомогательные методы или функции если необходимо.
Требования к реализации: ваш код не должен вводить или выводить что-либо, реализовывать функцию main не нужно.
*/
//-----------------------------------------------------------------------------

#include <iostream>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

struct Rational
{
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {};

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    double to_double() const {
        return numerator_ / (double) denominator_;
    }

    bool is_neg()
    {
        return numerator_ < 0;
    }

    bool is_eq()
    {
        return numerator_ == 0;
    }

private:
    int numerator_;
    int denominator_;
};

Rational& operator+=(Rational &left, const Rational &right) { left.add(right); return left; }
Rational& operator-=(Rational &left, const Rational &right) { left.sub(right); return left; }
Rational& operator*=(Rational &left, const Rational &right) { left.mul(right); return left; }
Rational& operator/=(Rational &left, const Rational &right) { left.div(right); return left; }

Rational operator+(Rational left) { return left; }
Rational operator-(Rational left) { left.neg(); return left; }

Rational operator + (Rational left, const Rational& right)
{
    return left += right;
}

Rational operator - (Rational left, const Rational& right)
{
    return left -= right;
}

Rational operator / (Rational left, const Rational& right)
{
    return left /= right;
}

Rational operator * (Rational left, const Rational& right)
{
    return left *= right;
}


//<, <=, >, >=, ==, !=

bool operator < (Rational left, Rational right)
{
    left.sub(right);

    return left.is_neg();
}

bool operator <= (Rational left, Rational right)
{
    left.sub(right);

    return left.is_neg() || left.is_eq();
}

bool operator > (Rational left, Rational right)
{
    right.sub(left);

    return right.is_neg();
}

bool operator >= (Rational left, Rational right)
{
    right.sub(left);

    return right.is_neg() || right.is_eq();
}

bool operator == (Rational left, Rational right)
{
    left.sub(right);

    return left.is_eq();
}

bool operator != (Rational left, Rational right)
{
    return !(left == right);
}

int main()
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(5);


    std::cout <<" < " << (r2 < r1) << std::endl;

    std::cout <<" 1/2 <= 1/2 " <<  bool(r1 <= r1) << std::endl;

    std::cout <<" > " << (r1 > r2) << std::endl;

    std::cout <<" >= " << (r1 >= r1) << std::endl;

    return 0;
}
