#include "Expression.hpp"
#include "Function.hpp"
#include "Operand.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>
calc::Expression::Expression(const std::string &s) {
    std::string current;
    for (char c: s + " ") {
        if (c == ' ') {
            if (current == "modulo" || current == "min" || current == "max" || current == "log" ||
                current == "pow" || current == "abs" || current == "sgn" || current == "floor" ||
                current == "ceil" || current == "frac" || current == "sin" || current == "cos" ||
                current == "atan" || current == "acot" || current == "ln" || current == "exp" ||
                current == "+" || current == "-" || current == "*" || current == "/")
                symbols.push(new Function(current));
            else if (current == "pi" || current == "fi" || current == "e")
                symbols.push(new Const(current));
            else {
                char *end;
                std::strtod(current.c_str(), &end);
                if (*end == '\0')
                    symbols.push(new Number(std::stod(current)));
                else if (current.length() <= 7 && current != "print" && current != "set" &&
                         current != "to" && current != "clear" && current != "exit")
                    symbols.push(new Variable(current));
                else
                    throw std::invalid_argument("Wrong variable  name");
            }
            current = "";
        } else
            current += c;
    }

}
double calc::Expression::eval() {
    std::stack<double> s;
    Symbol *symbol;
    while (!symbols.empty()) {
        symbol = symbols.front();
        symbols.pop();
        if (symbol->getArgsAmount() == 0)
            s.push(symbol->eval());
        else {
            double number1 = s.top();
            s.pop();
            if (symbol->getArgsAmount() == 1)
                s.push(symbol->eval(number1));
            else {
                double number2 = s.top();
                s.pop();
                s.push(symbol->eval(number2, number1));
            }
        }
    }
    return s.top();
}
