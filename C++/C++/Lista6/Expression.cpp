#include "Expression.h"


std::vector<std::pair<std::string, double>> Variable::vals;

std::string Number::label() {
    return std::to_string(num);
}

double Number::evaluate() {
    return num;
}

Variable::Variable(std::string n) {
    name = std::move(n);
    add_var(name, 0);
}

std::string Variable::label() {
    return name;
}

double Variable::evaluate() {
    for (const auto &p: vals) {
        if (p.first == name) {
            return p.second;
        }
    }
    return 0;
}

void Variable::add_var(const std::string &name, double val) {
    vals.emplace_back(name, val);
}

void Variable::delete_var(const std::string &name) {
    vals.erase(std::remove_if(vals.begin(), vals.end(),
                              [&](const std::pair<std::string, double> &p) { return p.first == name; }),
               vals.end());
}

void Variable::change_var(const std::string &name, double val) {
    for (auto &p: vals) {
        if (p.first == name) {
            p.second = val;
            return;
        }
    }
    add_var(name, val);
}

void Variable::printingVals() {
    if (vals.empty()) {
        cout << "The vector is empty!" << endl;
    }
    for (auto &p: vals) {
        cout << "(" << p.first << ":" << p.second << ")" << endl;
    }
}

double Constant::evaluate() {
    return value;
}

string Constant::label() {
    return name;
}

double Sin::evaluate() {
    return std::sin(arg->evaluate());
}

string Sin::label() {
    return "sin(" + arg->label() + ")";
}

double Cos::evaluate() {
    return std::cos(arg->evaluate());
}

string Cos::label() {
    return "cos(" + arg->label() + ")";
}

double Exp::evaluate() {
    return std::exp(arg->evaluate());
}

string Exp::label() {
    return "exp(" + arg->label() + ")";
}

double ln::evaluate() {
    if (arg->evaluate() <= 0) {
        throw std::invalid_argument("The log doesn't exist");
    }
    return std::log(arg->evaluate());
}

string ln::label() {
    return "ln(" + arg->label() + ")";
}

double Abs::evaluate() {
    return std::abs(arg->evaluate());
}

string Abs::label() {
    return "abs(" + arg->label() + ")";
}

double Opposite::evaluate() {
    return -1 * (arg->evaluate());
}

string Opposite::label() {
    return "opposite(" + arg->label() + ")";
}

double Inverse::evaluate() {
    if (arg->evaluate() == 0) {
        throw invalid_argument("Cannot divide by 0!");
    }
    return 1 / (arg->evaluate());
}

string Inverse::label() {
    return "Inverse(" + arg->label() + ")";
}


double Add::evaluate() {
    return left->evaluate() + right->evaluate();
}


string Add::label() {
    return "(" + left->label() + "+" + right->label() + ")";
}

double Subtract::evaluate() {
    return left->evaluate() - right->evaluate();
}

string Subtract::label() {
    return "(" + left->label() + "-" + right->label() + ")";
}

double Multiply::evaluate() {
    return left->evaluate() * right->evaluate();
}

string Multiply::label() {
    string result = left->label() + " * " + right->label();

    string left_str = left->label();
    string right_str = right->label();
    if (dynamic_cast<Add *>(left) || dynamic_cast<Add *>(right)) {
        // If either operand is an Add expression, wrap it in parentheses
        left_str = "(" + left_str + ")";
            right_str = "(" + right_str + ")";
    }
    if (dynamic_cast<Subtract *>(left) || dynamic_cast<Subtract *>(right)) {
        left_str = "(" + left_str + ")";

    }
    return left_str + "*" + right_str;
}

double Power::evaluate() {
    return std::pow(left->evaluate(), right->evaluate());
}

string Power::label() {
    string base_str = left->label();
    string exponent_str = right->label();
    if (dynamic_cast<Add *>(left)) {
        // If base is an Add expression, wrap it in parentheses
        base_str = "(" + base_str + ")";
    } else if (dynamic_cast<Multiply *>(left)) {
        // If base is a Multiply expression with lower precedence, wrap it in parentheses
        base_str = "(" + base_str + ")";
    }
    if (dynamic_cast<Power *>(right) || dynamic_cast<Multiply *>(right)) {
        // If exponent is a higher-precedence operator, wrap it in parentheses
        exponent_str = "(" + exponent_str + ")";
    }
    return base_str + "^" + exponent_str;
}

double Divide::evaluate() {
    if (right->evaluate() == 0) {
        throw std::invalid_argument("Cannot divide by 0");
    }
    return left->evaluate() / right->evaluate();
}

string Divide::label() {
    return "(" + left->label() + "/" + right->label() + ")";
}


double Log::evaluate() {
    double a = std::log(left->evaluate());
    double b = std::log(right->evaluate());
    if (a <= 0 || b <= 0 || a == 1)
        throw std::invalid_argument("Division by 0");
    return a / b;
}

string Log::label() {
    return "log(" + left->label() + ", " + right->label() + ")";
}


double modulo::evaluate() {
    double a = left->evaluate();
    double b = right->evaluate();
    if (a <= 0 || b <= 0)
        throw std::invalid_argument("The arguments are wrong");
    return (int) a % (int) b;
}

string modulo::label() {
    return "(" + left->label() + "%" + right->label() + ")";
}

