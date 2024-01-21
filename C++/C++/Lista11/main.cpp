#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <stdexcept>

namespace calculator {

    // Abstrakcyjna klasa reprezentująca symbol w wyrażeniu ONP
    class Symbol {
    public:
        virtual double eval() const = 0;
        virtual ~Symbol() {}
    };

    // Klasa reprezentująca operand
    class Operand : public Symbol {
    protected:
        double val;

    public:
        Operand(double n) : val(n) {}

        double eval() const override { return val; }
    };

    // Klasa reprezentująca liczbę
    class Number : public Operand {
    public:
        Number(double n) : Operand(n) {}
    };

    // Klasa reprezentująca zmienną
    class Variable : public Operand {
    private:
        std::string name;
        static std::unordered_map<std::string, double> vars;

    public:
        Variable(const std::string& varName) : Operand(0.0), name(varName) {}

        double eval() const override {
            auto it = vars.find(name);
            if (it == vars.end()) {
                throw std::runtime_error("Variable not found");
            }
            return it->second;
        }

        static void setVariable(const std::string& name, double value) {
            vars[name] = value;
        }

        static double getVariable(const std::string& name) {
            auto it = vars.find(name);
            if (it == vars.end()) {
                throw std::runtime_error("Variable not found");
            }
            return it->second;
        }
    };

    std::unordered_map<std::string, double> Variable::vars;

    // Klasa reprezentująca stałą
    class Constant : public Operand {
    private:
        std::string name;
        static const std::unordered_map<std::string, double> constants;

    public:
        Constant(const std::string& constName) : Operand(0.0), name(constName) {}

        double eval() const override {
            auto it = constants.find(name);
            if (it == constants.end()) {
                throw std::runtime_error("Constant not found");
            }
            return it->second;
        }
    };

    const std::unordered_map<std::string, double> Constant::constants = {
            { "e", 2.718281828459 },
            { "pi", 3.141592653589 },
            { "fi", 1.618033988750 }
    };

    // Abstrakcyjna klasa reprezentująca funkcję
    class Function : public Symbol {
    public:
        virtual double eval(double arg) const = 0;
    };

    // Klasy reprezentujące konkretne funkcje
    class Sin : public Function {
    public:
        double eval(double arg) const override {
            return std::sin(arg);
        }
    };

    class Cos : public Function {
    public:
        double eval(double arg) const override {
            return std::cos(arg);
        }
    };

    // Dodaj inne klasy reprezentujące funkcje

} // namespace calculator

using namespace calculator;

// Funkcja pomocnicza do sprawdzenia czy dany ciąg znaków jest liczbą
bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double num;
    return (iss >> num) && iss.eof();
}

// Funkcja pomocnicza do zamiany ciągu znaków na symbol
Symbol* parseSymbol(const std::string& str) {
    if (isNumber(str)) {
        double num = std::stod(str);
        return new Number(num);
    }
    else if (str.length() > 1 && str[0] == 'x') {
        std::string varName = str.substr(1);
        return new Variable(varName);
    }
    else {
        return new Constant(str);
    }
}

// Funkcja pomocnicza do zamiany operatora na funkcję
Function* parseFunction(const std::string& op) {
    if (op == "+") {
        return new Add();
    }
    else if (op == "-") {
        return new Subtract();
    }
    else if (op == "*") {
        return new Multiply();
    }
    else if (op == "/") {
        return new Divide();
    }
    else if (op == "%") {
        return new Modulo();
    }
    else if (op == "min") {
        return new Min();
    }
    else if (op == "max") {
        return new Max();
    }
    else if (op == "log") {
        return new Log();
    }
    else if (op == "pow") {
        return new Pow();
    }
        // Dodaj inne obsługiwane operatory/funkcje
    else {
        throw std::runtime_error("Unknown operator or function: " + op);
    }
}

// Funkcja pomocnicza do obliczania wartości wyrażenia ONP
double evaluate(const std::vector<Symbol*>& symbols) {
    std::stack<double> stack;

    for (Symbol* symbol : symbols) {
        if (Operand* operand = dynamic_cast<Operand*>(symbol)) {
            stack.push(operand->eval());
        }
        else if (Function* function = dynamic_cast<Function*>(symbol)) {
            if (stack.size() < 1) {
                throw std::runtime_error("Not enough operands for function");
            }
            double arg = stack.top();
            stack.pop();
            stack.push(function->eval(arg));
        }
        else {
            throw std::runtime_error("Invalid symbol in expression");
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.top();
}

int main() {
    std::string line;
    std::vector<Symbol*> symbols;
    bool shouldExit = false;

    while (!shouldExit && std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "print") {
            std::string expression;
            iss >> expression;

            try {
                symbols.clear();
                std::string token;
                while (iss >> token) {
                    symbols.push_back(parseSymbol(token));
                }

                double result = evaluate(symbols);
                std::cout << "Result: " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        else if (command == "set") {
            std::string variable;
            std::string expression;
            iss >> variable >> expression;

            try {
                symbols.clear();
                std::string token;
                while (iss >> token) {
                    symbols.push_back(parseSymbol(token));
                }

                double result = evaluate(symbols);
                Variable::setVariable(variable, result);
                std::cout << "Variable '" << variable << "' set to " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        else if (command == "clear") {
            Variable::clearVariables();
            std::cout << "Variables cleared" << std::endl;
        }
        else if (command == "exit") {
            shouldExit = true;
        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    // Zwolnij pamięć zajmowaną przez symbole
    for (Symbol* symbol : symbols) {
        delete symbol;
    }

    return 0;
}
