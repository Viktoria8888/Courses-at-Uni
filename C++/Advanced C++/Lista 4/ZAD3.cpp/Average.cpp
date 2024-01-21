#pragma once

template <typename T>
class Average
{
public:
    Average() : sum(0.0), l(0) {}

    void operator()(T elem)
    {
        sum += elem;
        l++;
        // std::cout << "Processed: " << elem << std::endl;
    }
    T get_sum() { return sum; }
    int get_l() { return l; }
    double get_avg()
    {
        if (get_l() != 0.0)
        {
            return static_cast<double>(get_sum()) / get_l();
        }
        else
        {
            return 0.0;
        }
    }

private:
    T sum;
    int l;
};
