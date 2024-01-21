#pragma once

#include <string>

class Symbol {
public:
    virtual double eval(double number1, double number2) const = 0;

    virtual double eval(double number) const = 0;

    virtual double eval() const = 0;

    int getArgsAmount() const;

protected:
    int argsAmount = 0;
};
