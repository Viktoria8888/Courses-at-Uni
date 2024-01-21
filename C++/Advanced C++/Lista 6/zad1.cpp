#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

class Person
{
private:
    string name;
    string surname;
    int age;
    double w;
    double h;

public:
    Person(string n, string s, int a, double w, double h) : name(n), surname(s), age(a), w(w), h(h) {}
    double bmi()
    {
        return w / (h * h);
    }
    void printInfo()
    {
        cout << "Name: " << name << " " << surname << ": Age " << age << ", Weight: " << w << ", Height: " << h << ", BMI: " << bmi() << endl;
    }
    double get_w()
    {
        return w;
    }
    double get_h()
    {
        return h;
    }
    int get_age()
    {
        return age;
    }
    void change_w(double new_w)
    {
        w = new_w;
    }
};

int main()
{
    deque<Person> d;
    d.emplace_back(Person("Adam", "Adamowicz", 19, 70, 174));
    d.emplace_back(Person("Artem,", "Nowak", 40, 100, 180));
    d.emplace_back(Person("Kacper,", "Kowalski", 25, 112, 190));
    d.emplace_back(Person("Nastia,", "Kowalska", 25, 120, 195));
    d.emplace_back(Person("Natalia,", "Dombrowska", 25, 60, 170));
    d.emplace_back(Person("Krystian", "Jankowski", 42, 78, 167));

    d.emplace_back(Person("Hanna", "Kulczcycka", 11, 40, 150));
    d.emplace_back(Person("Andrzej,", "Nowak", 38, 84, 191));
    d.emplace_back(Person("Kacper,", "Nowak", 27, 72, 177));
    d.emplace_back(Person("Alla,", "Kowalska", 25, 69, 155));
    d.emplace_back(Person("Ola,", "Stankiewicz", 50, 56, 169));
    d.emplace_back(Person("Basia", "Rachowska", 13, 45, 158));
    cout << "Sorting" << endl;
    sort(d.begin(), d.end(), [](Person &a, Person &b) -> bool
         { return a.bmi() < b.bmi(); });
    for (auto &p : d)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    cout << "Losing weight" << endl;
    for_each(d.begin(), d.end(), [](Person &a)
             { return a.change_w(a.get_w() * 0.9); });
    for (auto &p : d)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    cout << "Partition" << endl;

    auto it = partition(d.begin(), d.end(), [](Person &a)
                        { return a.get_w() >= 100; });
    deque<Person> heavy;
    copy(d.begin(), it, back_inserter(heavy));
    for (auto &p : heavy)
    {
        p.printInfo();
    }
    cout << "Light" << endl;
    deque<Person> light;
    copy(it, d.end(), back_inserter(light));
    for (auto &p : light)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    cout << "Average height" << endl;
    sort(d.begin(), d.end(), [](Person &a, Person &b) -> bool
         { return a.get_h() < b.get_h(); });
    for (auto &p : d)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    cout << "Shuffle elements" << endl;
    random_device rd;
    mt19937 gen(rd());

    shuffle(d.begin(), d.begin() + 4, gen);
    for (auto &p : d)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    shuffle(d.end() - 4, d.end(), gen);
    for (auto &p : d)
    {
        p.printInfo();
    }
    cout << "-----------------------------------" << endl;
    cout << "Youngest/Oldest" << endl;
    auto youngestPerson = std::min_element(d.begin(), d.end(),
                                           [](Person &a, Person &b)
                                           {
                                               return a.get_age() < b.get_age();
                                           });

    auto oldestPerson = std::max_element(d.begin(), d.end(),
                                         [](Person &a, Person &b)
                                         {
                                             return a.get_age() < b.get_age();
                                         });

    // Print the results
    std::cout << "Youngest person: ";
    youngestPerson->printInfo();

    std::cout << "Oldest person: ";
    oldestPerson->printInfo();
    return 0;
}
