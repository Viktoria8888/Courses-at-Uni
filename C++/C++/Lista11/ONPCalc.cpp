//
// Created by viktoria on 04.06.23.
//

#include <sstream>
#include "ONPCalc.h"

namespace calculator {
    std::map<std::string, double> Variable::vars;
    Queue<Symbol *> symbolQueue;

    void parse(const std::string &expression) {
        std::istringstream iss(expression);
        std::string token;
        while (iss >> token) {
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                double value = std::stod(token);
                symbolQueue.enqueue(new Number(value));
            } else if (isalpha(token[0])) {
                std::string name = token;
                if (Variable::vars.find(name) != Variable::vars.end()) {
                    double val = Variable::vars[name];
                    symbolQueue.enqueue(new Variable(name, val));
                }
            } else {
                // Token is an operator or function
                calculator::Function *function = nullptr;

                if (token == "+") {
                    function = new Addition();
                } else if (token == "-") {
                    function = new Subtraction();
                } else if (token == "*") {
                    function = new Multiplication();
                } else if (token == "/") {
                    function = new Division();
                } else if (token == "%") {
                    function = new Modulo();
                } else if (token == "min") {
                    function = new Min();
                } else if (token == "max") {
                    function = new Max();
                } else if (token == "log") {
                    function = new Log();
                } else if (token == "pow") {
                    function = new calculator::Pow();
                } else if (token == "abs") {
                    function = new calculator::Abs();
                } else if (token == "sgn") {
                    function = new calculator::Sgn();
                } else if (token == "floor") {
                    function = new calculator::Floor();
                } else if (token == "ceil") {
                    function = new calculator::Ceil();
                } else if (token == "frac") {
                    function = new calculator::Frac();
                } else if (token == "sin") {
                    function = new calculator::Sin();
                } else if (token == "cos") {
                    function = new calculator::Cos();
                } else if (token == "atan") {
                    function = new calculator::Atan();
                } else if (token == "acot") {
                    function = new calculator::Acot();
                } else if (token == "ln") {
                    function = new calculator::Ln();
                } else if (token == "exp") {
                    function = new calculator::Exp();
                }

                if (function != nullptr) {
                    symbolQueue.enqueue(function);
                } else {
                    std::cerr << "Unknown token: " << token << std::endl;
                }
            }
        }

