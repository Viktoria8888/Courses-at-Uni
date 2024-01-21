//
// Created by viktoria on 04.06.23.
//

#ifndef LISTA11_ONPCALC_H
#define LISTA11_ONPCALC_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>

namespace calculator {

    template<typename T>
    class Stack {
    public:
        void push(T expr);

        bool is_empty();

        T pop();

    private:
        std::vector<T> stack;
    };

    template<typename T>
    bool Stack<T>::is_empty() {
        return stack.empty();
    }

    template<class T>
    T Stack<T>::pop() {
        if (is_empty()) {
            std::cout << "The stack is empty :)" << std::endl;
        }
        return stack.pop_back();
    }

    template<class T>
    void Stack<T>::push(T expr) {
        stack.push_back();
    }

    template<class T>
    class Queue {
    public:
        void enqueue(T el);

        bool is_empty();

        T dequeue();

    private:
        std::vector<T> q;

    };

    template<class T>
    bool Queue<T>::is_empty() {
        return q.empty();
    }

    template<class T>
    T Queue<T>::dequeue() {
        if (is_empty()) {
            std::cout << "The queue is empty!" << std::endl;
        }
        return q[0];

    }

    template<class T>
    void Queue<T>::enqueue(T el) {
        q.push_back(el);
    }

    class Symbol {
        virtual double eval() = 0;
    };

    class Operand : public Symbol {
    protected:
        double val;
    public:
        Operand(double n) : val(n) {}

        double eval() override { return val; }
    };

    class Number : public Operand {
    public:
        Number(double n) : Operand(n) {}
    };

    class Variable : public Operand {
    private:
        std::string name;


    public:
        static std::map<std::string, double> vars;

        Variable(const std::string &varName, double val) : Operand(val), name(varName) {}

        static void setVariable(const std::string &name, double value) {
            vars[name] = value;
        }
    };

    class Constant : public Operand {
    private:
        std::string name;
        static const std::map<std::string, double> constants;

    public:
        Constant(const std::string &constName, double val) : Operand(val), name(constName) {}

    };

    const std::map<std::string, double> Constant::constants = {
            {"e",  2.718281828459},
            {"pi", 3.141592653589},
            {"fi", 1.618033988750}
    };

    class Function : public Symbol {
    public:
        virtual double eval() override {
            throw std::logic_error("Eval method not implemented for this function");
        }

    private:
        Sym
    };

    class Addition : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return arg1 + arg2;
        }
    };

    class Subtraction : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return arg1 - arg2;
        }
    };

    class Multiplication : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return arg1 * arg2;
        }
    };

    class Division : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            if (arg2 == 0) {
                throw std::runtime_error("Division by zero!");
            }
            return arg1 / arg2;
        }
    };

    class Modulo : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::fmod(arg1, arg2);
        }
    };

    class Min : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::min(arg1, arg2);
        }
    };

    class Max : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::max(arg1, arg2);
        }
    };

    class Log : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::log(arg2) / std::log(arg1);
        }
    };

    class Pow : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::pow(arg1, arg2);
        }
    };

    class Abs : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::abs(arg1);
        }
    };

    class Sgn : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return (arg1 > 0) - (arg1 < 0);
        }
    };

    class Floor : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::floor(arg1);
        }
    };

    class Ceil : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::ceil(arg1);
        }
    };

    class Frac : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            double dummy;
            return std::modf(arg1, &dummy);
        }
    };

    class Sin : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::sin(arg1);
        }
    };

    class Cos : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::cos(arg1);
        }
    };

    class Atan : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::atan(arg1);
        }
    };

    class Acot : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::atan(1.0 / arg1);
        }
    };

    class Ln : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::log(arg1);
        }
    };

    class Exp : public Function {
    public:
        double eval(double arg1, double arg2) const override {
            return std::exp(arg1);
        }
    };
}


#endif //LISTA11_ONPCALC_H
