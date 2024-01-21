#ifndef LISTA6_EXPRESSION_H
#define LISTA6_EXPRESSION_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>
#include <exception>
using namespace std;

class Expression {
public:
    Expression() {}

    virtual double evaluate() = 0;

    virtual std::string label() = 0;

    virtual ~Expression() {}

private:
    //Blockin g copying instances of the Expression class
    Expression(const Expression &);
    Expression &operator=(const Expression &);


};

class Number final: public Expression {
public:
    Number(double x) : num(x) {};

    ~Number() {}

    double evaluate();

    std::string label();

private:
    double num;
};

class Variable final : public Expression {
public:
    Variable(std::string n);

    ~Variable() {}

    static void add_var(const std::string &name, double val);

    static void delete_var(const std::string &name);

    static void change_var(const std::string &name, double val);

    string label();

    double evaluate();

    static void printingVals();

private:
    std::string name;
    static std::vector<std::pair<std::string, double>> vals;
};

class Constant : public Expression {
public:
    Constant(string n, double val) : name(n), value(val) {}

    ~Constant() {}

    double evaluate();

    string label();

private:
    const double value;
    string name;
};

class Pi final : public Constant {
public:
    Pi() : Constant("pi", 3.14159265358979323846) {}
};

class E final : public Constant {
public:
    E() : Constant("e", 2.71828182845904523536) {}
};

class Fi final : public Constant {
public:
    Fi() : Constant("fi", 1.61803398875) {}
};

// OPERATORS

class Operator1Arg : public Expression {
public:
    virtual double evaluate() = 0;

    virtual string label() = 0;
};

class Sin final : public Operator1Arg {
public:
    Sin(Expression *arg) : arg(arg) {}

    ~Sin() override { delete arg; }

    double evaluate();

    string label();

private:
    Expression *arg;
};

class Cos final : public Operator1Arg {
public:
    Cos(Expression *arg) : arg(arg) {}

    ~Cos() { delete arg; }

    double evaluate();

    string label();

private:
    Expression *arg;
};

class Exp final : public Operator1Arg {
public:
    Exp(Expression *arg) : arg(arg) {}

    ~Exp() { delete arg; }

    double evaluate();

    string label();

private:
    Expression *arg;
};

class ln final : public Operator1Arg {
public:
    ln(Expression *arg) : arg(arg) {}

    ~ln() { delete arg; }

    double evaluate();

    string label();

private:
    Expression *arg;
};

class Abs final : public Operator1Arg {
public:
    Abs(Expression *arg) : arg(arg) {}
    ~Abs() { delete arg; }
    double evaluate();
    string label();

private:
    Expression *arg;
};

class Opposite final : public Operator1Arg {
public:
    Opposite(Expression *arg) : arg(arg) {}

    ~Opposite() { delete arg; }

    double evaluate();
    string label();
private:
    Expression *arg;
};

class Inverse final : public Operator1Arg {
public:
    Inverse(Expression *arg) : arg(arg) {}

    ~Inverse() { delete arg; }

    double evaluate();

    string label();
private:
    Expression *arg;
};

class Operator2Arg : public Expression {
public:
    Operator2Arg(Expression *l, Expression *r) : left(l), right(r) {}

    ~Operator2Arg() {
        delete left;
        delete right;
    }

protected:
    Expression *left;
    Expression *right;
};


class Add : public Operator2Arg {
public:
    Add(Expression *l, Expression *r) : Operator2Arg(l, r) {}

    double evaluate();

    string label();

};

class Subtract : public Operator2Arg {
public:
    Subtract(Expression *l, Expression *r) : Operator2Arg(l, r) {}

    double evaluate();

    string label();

};

class Multiply : public Operator2Arg {
public:
    Multiply(Expression *l, Expression *r) : Operator2Arg(l, r) {}

    double evaluate();

    string label();

};


class Divide : public Operator2Arg {
public:
    Divide(Expression *l, Expression *r) : Operator2Arg(l, r) {}

    string label();

    double evaluate();

};

class Power : public Operator2Arg {
public:
    Power(Expression *l, Expression *r) : Operator2Arg(l, r) {}

    string label();

    double evaluate();

};

class Log : public Operator2Arg{
public:
    Log(Expression *l, Expression *r) : Operator2Arg(l,r){}
    string label();
    double evaluate();

};

class modulo final : public Operator2Arg {

public:
    modulo(Expression *a, Expression *b) : Operator2Arg(a, b) {}
    string label();
    double evaluate();

};


#endif
