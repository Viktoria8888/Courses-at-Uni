#pragma once

template <typename T>
class SumElements
{
public:
    SumElements() : is_res(false) {}
    void operator()(T &elem)
    {
        if (!is_res)
        {
            is_res = true;
            res = elem;
        }
        res += elem;
    }
    T get_sum()
    {
        return res;
    }

private:
    bool is_res;
    T res;
};
