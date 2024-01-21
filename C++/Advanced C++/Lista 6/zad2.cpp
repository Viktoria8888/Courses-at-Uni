#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Point
{
private:
    int r;
    int g;
    int b;
    string name;

public:
    Point(int r, int g, int b, string name) : r(r), g(g), b(b), name(name) {}
    string get_name()
    {
        return name;
    }
    int get_r()
    {
        return r;
    }
    int get_g()
    {
        return g;
    }
    int get_b()
    {
        return b;
    }
    double get_luminance(){
        return (0.3 * get_r() + 0.59 * get_g() + 0.11 * get_b());
    }

    void printInfo()
    {
        cout << "Name: " << name << ", RGB: (" << r << ", " << g << ", " << b << ")" <<" Luminance: " << get_luminance()<< endl;
    }
};

void printPoints( list<Point> &points)
{
    for (auto &point : points)
    {
        point.printInfo();
    }
}

int main()
{
    list<Point> points = {
        {255, 0, 0, "Red"},
        {0, 255, 0, "Green"},
        {0, 0, 255, "Blue"},
        {255, 255, 0, "Yellow"},
        {128, 0, 128, "Purple"},
        {0, 128, 128, "Teal"},
        {255, 165, 0, "Orange"},
        {255, 192, 203, "Pink"},
        {0, 128, 0, "Dark green"},
        {70, 130, 180, "Steel Blue"},
        {255, 69, 0, "Red-Orange"},
        {0, 0, 128, "Navy"},
        {139, 69, 19, "Saddle Brown"},
        {0, 255, 255, "Cyan"},
        {255, 215, 0, "Gold"},
        {255, 99, 71, "Tomato"},
        {0, 255, 127, "Spring Green"},
        {255, 0, 255, "Magenta"},
        {128, 128, 0, "Olive"},
        {255, 20, 147, "Deep Pink"},
        {0, 0, 0, "Black"},
        {255, 255, 255, "White"},
        {128, 128, 128, "Gray"}

    };
    cout << "Filtering the list based on name length: \n";
    auto it = remove_if(points.begin(), points.end(), [](Point &a)
                        { return a.get_name().length() >= 5; });
    points.erase(it, points.end());
    printPoints(points);
    cout << "Coordinate plane \n";
    int quadrantCounts[4] = {
        count_if(points.begin(), points.end(), [](Point &p)
                 { return p.get_r() > 0 && p.get_g() > 0; }),
        count_if(points.begin(), points.end(), [](Point &p)
                 { return p.get_r() < 0 && p.get_g() > 0; }),
        count_if(points.begin(), points.end(), [](Point &p)
                 { return p.get_r() < 0 && p.get_g() < 0; }),
        count_if(points.begin(), points.end(), [](Point &p)
                 { return p.get_r() > 0 && p.get_g() < 0; })};

    cout << "Quadrant I: " << quadrantCounts[0] << " points" << endl;
    cout << "Quadrant II: " << quadrantCounts[1] << " points" << endl;
    cout << "Quadrant III: " << quadrantCounts[2] << " points" << endl;
    cout << "Quadrant IV: " << quadrantCounts[3] << " points" << endl;


    // Sorting points
    vector<Point> pointsVector(points.begin(), points.end());
    sort(pointsVector.begin(), pointsVector.end(), [](Point &a,  Point &b)
         { return (0.3 * a.get_r() + 0.59 * a.get_g() + 0.11 * a.get_b()) <
                  (0.3 * b.get_r() + 0.59 * b.get_g() + 0.11 * b.get_b()); });


    points.assign(pointsVector.begin(), pointsVector.end());
    printPoints(points);
    cout<< "Dark points \n";
    list<Point> dark_points;
    auto it2 = remove_if(points.begin(), points.end(), [](Point& a){ return (0.3 * a.get_r() + 0.59 * a.get_g() + 0.11 * a.get_b()) > 64;});
    move(points.begin(), it2,back_inserter(dark_points));
    printPoints(dark_points);

    return 0;
}
