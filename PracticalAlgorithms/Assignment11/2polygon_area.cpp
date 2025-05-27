#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point {
    ll x, y;
};

ll triangle_area_2x(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    Point base = pts[0];
    ll area_2x = 0;
    for (int i = 1; i < n - 1; i++) {
        area_2x += triangle_area_2x(base, pts[i], pts[i + 1]);
    }

    ll abs_area_2x = abs(area_2x);
    ll whole = abs_area_2x / 2;
    bool half = abs_area_2x % 2;

    if (half) {
        cout << whole << ".5\n";
    } else {
        cout << whole << ".0\n";
    }

    return 0;
}