#pragma once
#include <utility>
template <typename T>
class MaxMin
{
public:
    MaxMin() : is_min(false), is_max(false) {}
    void operator()(T &elem)
    {
        if (!is_max || elem > max)
        {
            is_max = true;
            max = elem;
        }
        if (!is_min || elem < min)
        {
            is_min = true;
            min = elem;
        }
    }
    std::pair<T, T> getMinMax()
    {
        return {max, min};
    }

private:
    bool is_min;
    bool is_max;
    T min;
    T max;
};
