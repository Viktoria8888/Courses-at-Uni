
class PrintKthElem
{
public:
    PrintKthElem(int k, int p) : k(k), p(p) {}
    template <typename Arg>
    void operator()(Arg &elem)
    {
        if (curr >= p && (curr - p) % k == 0)
        {
            std::cout << elem << std::endl;
        }
        curr++;
    }

private:
    int k;
    int p;
    int curr;
};
