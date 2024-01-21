#include "Operand.hpp"
#include <stdexcept>

namespace calc {
    double Operand::eval() const {
        return value;
    }
    void Operand::setValue(double v) {
        value = v;
    }
    Variable::Variable(const std::string &n) : Operand() {
        name = n;
    }

    std::map<std::string, double> Variable::vals;

    void Variable::setVariable(const std::string &n, double value) {
        if (Variable::vals.count(n) > 0) {
            Variable::vals.erase(n);
        }
        Variable::vals[n] = value;
    }
    void Variable::clearVariables() {
        Variable::vals.clear();
    }
    double Variable::eval() const {
        if (Variable::vals.count(name) > 0)
            return Variable::vals[name];
        else
            throw std::invalid_argument("There is no defined value for this variable");
    }
    Number::Number(double v) : Operand() {
        setValue(v);
    }
    Const::Const(const std::string &type) : Operand() {
        if (type == "pi")
            setValue(3.141592653589);
        else if (type == "e")
            setValue(2.718281828459);
        else if (type == "fi")
            setValue(1.618033988750);
        else
            throw std::invalid_argument("The constant was not found");
    }


}
