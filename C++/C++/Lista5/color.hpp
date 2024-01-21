#include <algorithm>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
class Color
{
public:
    Color() : r(0), g(0), b(0) {}
    Color(int c1, int c2, int c3);

    int get_r() const { return r; }
    int get_g() const { return g; }
    int get_b() const { return b; }
    void set_r(int c)
    {
        if (c < 0 || c > 255)
        {
            throw std::invalid_argument("Invalid value");
        }
        r = c;
    }
    void set_g(int c)
    {
        if (c < 0 || c > 255)
        {
            throw std::invalid_argument("Invalid value");
        }
        g = c;
    }
    void set_b(int c)
    {
        if (c < 0 || c > 255)
        {
            throw std::invalid_argument("Invalid color value");
        }
        b = c;
    }

    void brighten(float factor);

    void darken(float factor);

    static Color color_combination(Color &c1, Color &c2);

    void display()
    {
        std::cout << "r:" << r << " "
                  << "g:" << g << " "
                  << "b:" << b << std::endl;
    }

private:
    int r;
    int g;
    int b;
};

class ColorTransparent : virtual public Color
{
public:
    ColorTransparent() : transparency(255) {}
    ColorTransparent(int c1, int c2, int c3, int t) : Color(c1, c2, c3), transparency(t) {}

    int get_transparency() const { return transparency; }
    void set_transparency(int t)
    {
        if (t < 0 || t > 255)
        {
            throw std::invalid_argument("Invalid transparency value");
        }
        transparency = t;
    }

private:
    int transparency;
};

class ColorName : public virtual Color
{
public:
    ColorName() : name("") {}
    ColorName(int c1, int c2, int c3, const std::string &n) : Color(c1, c2, c3), name(n) {}
    std::string get_name() const { return name; }
    void set_name(const std::string &n);

private:
    std::string name;
};

class Colornt : public ColorName, public ColorTransparent
{
    Colornt(int c1, int c2, int c3, const std::string &n, int t) : ColorName(c1, c2, c3, n), ColorTransparent(c1, c2, c3, t) {}
};

class Pixel
{
public:
    static std::string RESOLUTION;
    static int HEIGHT;
    static int WIDTH;
    Pixel() : x(0), y(0) {}
    Pixel(int a, int b) : x(a), y(b) {}

    int get_x() const { return x; }
    int get_y() const { return y; }

    void set_x(int a);
    void set_y(int b);

private:
    int x;
    int y;
};

class Vector // can come in handy
{

private:
    int a;
    int b;
};

class ColoredPixel : public Pixel,
                     public ColorTransparent
{
public:
    ColoredPixel(int x, int y, int r, int g, int b, int t) : Pixel(x, y), ColorTransparent(r, g, b, t) {}

    void move(int x_vector, int y_vector)
    {
        int new_x = get_x() + x_vector;
        int new_y = get_y() + y_vector;
        if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT)
        {
            throw std::out_of_range("Pixel IS out the screen");
        }
        set_x(new_x);
        set_y(new_y);
    }
};
