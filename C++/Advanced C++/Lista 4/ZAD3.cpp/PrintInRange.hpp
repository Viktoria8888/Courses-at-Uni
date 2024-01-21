#pragma once
template <typename A, typename B>
class PrintInRange
{
public:
    PrintInRange(A a, B b) : a(a), b(b) {}

    template <typename Arg>
    void operator()(Arg& elem)
    {
        if (a < elem && elem < b)
        {
            std::cout << elem << std::endl;
        }
    }

private:
    A a;
    B b;
};
