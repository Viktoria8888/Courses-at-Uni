
struct FU
{
    int o;
    int rozm;
};
FU tab[1000007];

void init(int n)
{
    for (int i = 0; i < n + 3; i++)
    {
        tab[i].o = i;
        tab[i].rozm = 1;
    }
}

int Find(int nr)
{
    if (tab[nr].o == nr)
        return nr;
    tab[nr].o = Find(tab[nr].o);
    return tab[nr].o;
}

bool Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    if (a == b)
        return 0;

    if (tab[a].rozm < tab[b].rozm)
        swap(a, b);
    tab[a].rozm += tab[b].rozm;
    tab[b].o = a;
    return 1;
}

