#pragma once

#include "Symbol.hpp"
#include <string>
#include <map>

namespace calc {
    class Operand : public Symbol {
    public:
        double eval(double number1, double number2) const override { return 0; };

        double eval(double number) const override { return 0; };

        double eval() const override;

        void setValue(double v);

    private:
        double value;
    };

    class Variable : public Operand {
    public:
        explicit Variable(const std::string &n);

        double eval() const override;

    private:
        std::string name;
    public:
        static void setVariable(const std::string &name, double value);

        static void clearVariables();

        static std::map<std::string, double> vals;
    };

    class Number : public Operand {
    public:
        explicit Number(double v);
    };

    class Const : public Operand {
    public:
        explicit Const(const std::string &type);
    };
}