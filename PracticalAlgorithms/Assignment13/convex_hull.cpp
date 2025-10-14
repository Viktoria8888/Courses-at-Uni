#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point
{
    long long x, y;
    bool operator<(const Point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

long long cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point> points)
{
    sort(points.begin(), points.end());

    vector<Point> lower;
    for (const Point &p : points)
    {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower[lower.size() - 1], p) < 0)
        {
            lower.pop_back();
        }
        lower.push_back(p);
    }

    vector<Point> upper;
    for (int i = points.size() - 1; i >= 0; i--)
    {
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper[upper.size() - 1], points[i]) < 0)
        {
            upper.pop_back();
        }
        upper.push_back(points[i]);
    }

    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main()
{
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convexHull(points);

    sort(hull.begin(), hull.end());

    cout << hull.size() << endl;
    for (const Point &p : hull)
    {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}