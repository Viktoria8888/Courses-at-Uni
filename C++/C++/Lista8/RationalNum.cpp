//
// Created by viktoria on 03.05.23.
//

#include <stdexcept>
#include "RationalNum.h"

namespace rational_num {
    std::string fractionToDecimal(int numerator, int denominator) {

        if (numerator == 0) { return "0"; }

        std::string ans;

        int new_num = numerator;
        if (numerator < 0) {
            //ans += "-";
            new_num = (-1) * numerator;
        }

        long remainder = new_num % denominator;

        std::string x = std::to_string(new_num / denominator);
        ans += x;

        if (remainder == 0) {
            return ans;
        }
        ans.push_back('.');

        std::map<int, int> m;
        while (remainder != 0) {
            if (m.find(remainder) != m.end()) { // if the remainder already appeared in the map
                ans.insert(ans.begin() + m[remainder], '(');
                ans += ")";
                break;
            } else {
                m[remainder] = ans.size();
                remainder *= 10;
                ans += std::to_string(remainder / denominator);
                remainder %= denominator;
            }
        }
        return ans;
    }

    int64_t gcd(int64_t a, int64_t b) {
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        return std::abs(a);
    }

    int RationalNum::getDenominator() const {
        return denominator;
    }

    RationalNum::RationalNum(int num, int den) {
        if (den == 0) {
            throw DivisionByZero();
        }
        int numerator1 = num;
        int  denominator1 = den;
        if (den < 0) {
            numerator1 = -1 * num;
            denominator1 = -1 * den;
        }
        int gcd_nums = gcd(num, den);
        numerator = numerator1 / gcd_nums;
        denominator = denominator1 / gcd_nums;
    }


    void RationalNum::setNumerator(int num) {
        numerator = num;
    }

    int RationalNum::getNumerator() const {
        return numerator;
    }

    void RationalNum::setDenominator(int den) {
        denominator = den;
    }

//    RationalNum RationalNum::operator+(const RationalNum &frac) {
//        int64_t new_num = static_cast<int64_t>(this->getNumerator())*static_cast<int64_t>(frac.getDenominator())
//                + static_cast<int64_t>(frac.getNumerator())*static_cast<int64_t>(this->getDenominator());
//        int64_t new_den = static_cast<int64_t>(this->getDenominator()) * static_cast<int64_t>(frac.getDenominator());
//
//        int64_t n = gcd(new_num, new_den);
//        new_num /= n;
//        new_den /= n;
//
//        if (new_num > std::numeric_limits<int>::max() || new_den < std::numeric_limits<int>::min()) {
//            throw RangeOverflow();
//        }
//        return RationalNum(new_num, new_den);
    //}

    RationalNum RationalNum::operator-(const RationalNum &frac) const {
        int64_t new_num = static_cast<int64_t>(this->getNumerator())*frac.getDenominator() - static_cast<int64_t>(frac.getNumerator())*this->getDenominator();
        int64_t new_den = static_cast<int64_t>(this->getDenominator()) * frac.getDenominator();

        int n = gcd(new_num, new_den);
        new_num /= n;
        new_den /= n;

        if (new_num > std::numeric_limits<int>::max() || new_den < std::numeric_limits<int>::min()) {
            throw RangeOverflow();
        }
        return RationalNum(new_num, new_den);
    }

    RationalNum RationalNum::operator/(const RationalNum &frac) {
        int64_t new_num = static_cast<int64_t>(this->getNumerator()) * frac.getDenominator();
        int64_t new_den = static_cast<int64_t>(this->getDenominator()) * frac.getNumerator();

        int n = gcd(new_num, new_den);
        new_num /= n;
        new_den /= n;

        if (new_num > std::numeric_limits<int>::max() || new_den < std::numeric_limits<int>::min()) {
            throw RangeOverflow();
        }
        if (new_den == 0) {
            throw DivisionByZero();
        }
        return RationalNum(new_num, new_den);
    }

    RationalNum RationalNum::operator*(const RationalNum &frac) {
        int64_t new_num = static_cast<int64_t>(this->getNumerator()) * frac.getNumerator();
        int64_t new_den = static_cast<int64_t>(this->getDenominator()) * frac.getDenominator();

        int n = gcd(new_num, new_den);
        new_num /= n;
        new_den /= n;

        if (new_num > std::numeric_limits<int>::max() || new_den < std::numeric_limits<int>::min()) {
            throw RangeOverflow();
        }
        return RationalNum(new_num, new_den);
    }

    RationalNum RationalNum::operator-() {
        return RationalNum(this->numerator * (-1), this->denominator);
    }

    RationalNum RationalNum::operator!() {
        if (this->getNumerator() == 0) {
            throw DivisionByZero();
        }
        return RationalNum((-1) * this->getDenominator(), (-1) * this->getNumerator());
    }

    RationalNum::operator int() const {
        return round((double)this->numerator / this->denominator);
    }

    RationalNum::operator double() const {
        return (double)this->numerator / this->denominator;
    }

    std::ostream &operator<<(std::ostream &os, const RationalNum &frac) {

        os << fractionToDecimal(frac.getNumerator(), frac.getDenominator());
        return os;
    }

    void RationalNum::print_frac() const {
        std::cout << this->numerator << "/" << this->denominator<<std::endl;
    }

    RationalNum operator+(const RationalNum &r1, const RationalNum &frac) {
        int64_t new_num = static_cast<int64_t>(r1.getNumerator())*static_cast<int64_t>(frac.getDenominator())
                + static_cast<int64_t>(frac.getNumerator())*static_cast<int64_t>(r1.getDenominator());
        int64_t new_den = static_cast<int64_t>(r1.getDenominator()) * static_cast<int64_t>(frac.getDenominator());

        int64_t n = gcd(new_num, new_den);
        new_num /= n;
        new_den /= n;

        if (new_num > std::numeric_limits<int>::max() || new_den < std::numeric_limits<int>::min()) {
            throw RangeOverflow();
        }
        return RationalNum(new_num, new_den);
    }


} // rational_num