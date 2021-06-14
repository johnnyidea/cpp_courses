
/*
Задача:
Определите для класса Rational операторы сложения, вычитания, умножения и деления, так чтобы объекты типа Rational
можно было складывать (вычитать, умножать и делить) не только друг с другом но и с целыми числами.
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

int main()
{
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(5);

    r1.add(r2);
    std::cout << r1.to_double() << std::endl;
    r1.sub(r2);
    std::cout << r1.to_double() << std::endl;
    r1.neg();
    std::cout << r1.to_double() << std::endl;
    r3.mul(r1);
    std::cout << r3.to_double() << std::endl;
    r3.div(r2);
    std::cout << r3.to_double() << std::endl;

	return 0;
}
