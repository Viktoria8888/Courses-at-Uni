//
// Created by viktoria on 03.05.23.
//

#ifndef LISTA8_RATIONALNUM_H
#define LISTA8_RATIONALNUM_H

#include <exception>
#include <ostream>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <limits>

namespace rational_num {

    class ExceptionsRationalNum : public std::logic_error {
    public:
        ExceptionsRationalNum(const std::string &what_arg) : logic_error(what_arg) {}
    };

    class DivisionByZero : public ExceptionsRationalNum {
    public:
        DivisionByZero() : ExceptionsRationalNum("Division by zero error") {}
    };

    class RangeOverflow : public ExceptionsRationalNum {
    public:
        RangeOverflow() : ExceptionsRationalNum("Range overflow error") {}
    };

    int64_t gcd( int64_t a,  int64_t b);

    std::string fractionToDecimal(int numerator, int denominator);

    class RationalNum {
    public:

        RationalNum() : numerator(0), denominator(1) {}

        RationalNum(int num, int den = 1);

        int getNumerator() const;

        int getDenominator() const;

        void setNumerator(int numerator);

        void setDenominator(int denominator);

        //RationalNum operator+(const RationalNum &frac) noexcept(false);

        RationalNum operator-(const RationalNum &frac) const;

        RationalNum operator/(const RationalNum &frac) noexcept(false);

        RationalNum operator*(const RationalNum &frac) noexcept(false);

        RationalNum operator-();

        RationalNum operator!() noexcept(false);

        explicit operator int() const;

        explicit operator double() const;

        friend std::ostream &operator<<(std::ostream &os, const RationalNum &frac);

        friend RationalNum operator+(const RationalNum& r1, const RationalNum &r2);
        void print_frac() const;


    private:
        int numerator;
        int denominator;
    };
    RationalNum operator+(const RationalNum& r1, const RationalNum &r2);
}

#endif //LISTA8_RATIONALNUM_H