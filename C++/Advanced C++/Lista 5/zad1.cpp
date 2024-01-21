
#include <unordered_set>
#include <vector>
#include <stack>
#include "Symbol.cpp"



std::forward_list<Symbol> convertToPostfix(std::forward_list<Symbol> input)
{   std::stack<Symbol> st;
    std::forward_list<Symbol> res;
    // to insert back
    auto before_end = res.before_begin();


    for (auto &e : input)
    {
        cout<<e.get_name()<<endl;
        switch (e.get_type())
        {
        case Type::Number:
        case Type::Variable:
        case Type::Constant:
            res.insert_after(before_end,e);
            before_end++;
            break;
        case Type::Function:
        case Type::LP:
            st.push(e);
            break;
        case Type::Operand:
            // case Type::Function:
            while (!st.empty() && st.top().get_priority() >= e.get_priority())
            {
                res.insert_after(before_end,st.top());
                before_end++;
                st.pop();
            }
            st.push(e);
            break;

        case Type::RP:
            while (!st.empty() && st.top().get_type() != Type::LP)
            {
                res.insert_after(before_end,st.top());
                before_end++;
                st.pop();
            }
            st.pop(); // popping (
            if (!st.empty() && st.top().get_type() == Type::Function)
            {
                res.insert_after(before_end,st.top());
                before_end++;
                st.pop();
            }
            break;
        }
    }
    while (!st.empty())
    {
        res.insert_after(before_end,st.top());
        before_end++;
        st.pop();
    }
    return res;
}

int main()
{
    string s = "42 / 6 + cos ( ( ( pi )";
    std::forward_list<Symbol> res = convertToPostfix(stringToForwardList(s));

    for (auto &element : res)
    {
        element.printValues();
    }

    return 0;
}
