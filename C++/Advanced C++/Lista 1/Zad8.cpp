#include <iostream>
#include <tuple>
#include <string>
#include <deque>
#include <algorithm>
class Osoba
{
private:
    std::string name;
    std::string surname;
    int year;

public:
    Osoba(std::string name, std::string surname, int year) : name(name), surname(surname), year(year) {}
    friend bool operator<(const Osoba &a, const Osoba &b);
    void print() const;
};
bool operator<(const Osoba &a, const Osoba &b)
{
    return std::tie(a.name, a.surname, a.year) < std::tie(b.name, b.surname, b.year);
}

void Osoba::print() const
{
    std::cout << name << " " << surname << " " << year << std::endl;
}
int main()
{
    std::deque<Osoba> people;
    people.push_back(Osoba("Oleksandr", "Tsesenko", 2005));
    people.push_back(Osoba("Antoni", "Klymczuk", 1990));
    people.push_back(Osoba("Daria", "Kowalczuk", 1995));
    people.push_back(Osoba("Anastasia", "Gryhorenko", 2000));
    std::sort(people.begin(), people.end());
    for (const Osoba &person : people)
    {
        person.print();
    }
    return 0;
}
