#pragma once
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_set>
#include <forward_list>
#include <sstream>
using namespace std;

enum class Type
{
    Number,
    Variable,
    Operand, // +, -, *, /
    Function,
    Constant,
    LP, // Ludowa Polska
    RP  // Rzeczpospolita Polska
};
bool isDouble(const std::string &s)
{
    try
    {
        size_t pos;
        std::stod(s, &pos);

        return pos == s.length();
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
}

class Symbol
{
public:
    static unordered_set<pair<string, double>> vars;
    Symbol(string token) : priority(0)
    {
        Type t;
        double n = 0.0;
        string str = token;

        std::unordered_set<std::string> funs = {"sin", "cos", "tan"};

        if (token == "+" || token == "-")
        {
            t = Type::Operand;
            priority = 1;

        }
        else if (token == "*" || token == "/")
        {
            t = Type::Operand;
            priority = 2;
        }
        else if (funs.count(token) > 0)
        {
            t = Type::Function;
            str = token;
        }
        else if (isDouble(token))
        {
            t = Type::Number;
            n = stod(token);
        }
        else if (token == "pi")
        {
            t = Type::Constant;
            n = 3.141592654;
            str = token;
        }
        else if (token == "e")
        {
            t = Type::Constant;
            n = 2.718281828;
            str = token;
        }
        else if (token == ")")
        {
            t = Type::RP;
        }
        else if (token == "(")
        {
            t = Type::LP;
        }
        else
        {
            t = Type::Variable;

            str = token;
        }

        tp = std::make_tuple(t, n, str);
    }
    Type get_type()
    {
        return std::get<0>(tp);
    }
    double get_val()
    {
        return std::get<1>(tp);
    }
    string get_name()
    {
        return std::get<2>(tp);
    }
    int get_priority()
    {
        return priority;
    }
    void printValues() const
    {
        std::cout << "Type: ";
        switch (std::get<0>(tp))
        {
        case Type::Number:
            std::cout << "Number";
            break;
        case Type::Variable:
            std::cout << "Variable";
            break;
        case Type::Operand:
            std::cout << "Operand";
            break;
        case Type::Function:
            std::cout << "Function";
            break;
        case Type::Constant:
            std::cout << "Constant";
            break;

        case Type::LP:
            std::cout << "LP";
            break;

        case Type::RP:
            std::cout << "RP";
            break;
        }

        std::cout << ", Value: " << std::get<1>(tp);
        std::cout << ", String: " << std::get<2>(tp) << std::endl;
    }

private:
    tuple<Type, double, string>
        tp;
    int priority;
};

// std::forward_list<Symbol> stringToForwardList( std::string &expr) <- nie działa
// {

//     std::forward_list<Symbol> symbols;
//     std::istringstream iss(expr);
//     std::string token;
//     while (iss >> token)
//     {
//         symbols.push_front(Symbol(token));
//     }
//     return symbols;
// }
std::forward_list<Symbol> stringToForwardList(std::string &expr)
{
    std::forward_list<Symbol> symbols;
    auto before_end = symbols.before_begin();

    std::istringstream iss(expr);
    std::string token;
    while (iss >> token)
    {
        symbols.insert_after(before_end, Symbol(token));
        before_end++;
    }
    return symbols;
}
// std::forward_list<Symbol> stringToForwardList(std::string &expr)
// {
//     std::forward_list<Symbol> symbols;
//     std::vector<std::string> tokens;
//     std::istringstream iss(expr);
//     std::string token;
//     while (getline(iss, token, ' ')) {
//         tokens.push_back(token);
//     }
//     reverse(tokens.begin(),tokens.end());
//     for (auto& i: tokens){
//         symbols.push_front(Symbol(i));}

//     return symbols;

// }
