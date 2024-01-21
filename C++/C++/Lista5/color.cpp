#include "color.hpp"

int Pixel::HEIGHT = 1080;
int Pixel::WIDTH = 1920;
std::string Pixel::RESOLUTION = "HDTV1080";

Color Color::color_combination(Color c1, Color c2)
{
    int r = (c1.get_r() + c2.get_r()) / 2;
    int g = (c1.get_g() + c2.get_g()) / 2;
    int b = (c1.get_b() + c2.get_b()) / 2;
    return Color(r, g, b);
}

Color::Color(int c1, int c2, int c3)
{

    if (c1 < 0 || c1 > 255 || c2 < 0 || c2 > 255 || c3 < 0 || c3 > 255)
    {
        throw std::invalid_argument("Invalid value");
    }
    r = c1;
    g = c2;
    b = c3;
}

void Color::brighten(float factor)
{
    r = static_cast<int>(std::max(r * factor, 0.0f));
    g = static_cast<int>(std::max(g * factor, 0.0f));
    b = static_cast<int>(std::max(b * factor, 0.0f));
    r = std::min(255, r);
    g = std::min(255, g);
    b = std::min(255, b);
}

void Color::darken(float factor)
{
    r = static_cast<int>(std::min(r * factor, 255.0f));
    g = static_cast<int>(std::min(g * factor, 255.0f));
    b = static_cast<int>(std::min(b * factor, 255.0f));
    r = std::max(0, r);
    g = std::max(0, g);
    b = std::max(0, b);
}

void ColorName::set_name(const std::string &n)
{
    for (char c : n) // using foreach loop instead of usual one
    {
        if (!islower(c))
        {
            throw std::invalid_argument("No capital letters should be used!");
        }
    }
    name = n;
}

void Pixel::set_x(int a)
{
    if (a < 0 || a > HEIGHT)
    {
        throw std::invalid_argument("The pixel would be out the screen");
    }
    x = a;
}

void Pixel::set_y(int a)
{
    if (a < 0 || a > WIDTH)
    {
        throw std::invalid_argument("The pixel would be out the screen");
    }
    y = a;
}

int distance(const Pixel& p, const Pixel& q){
    int dx = p.get_x() - q.get_x();
    int dy = p.get_y() - q.get_y();
    return std::sqrt(dx*dx + dy*dy);
}


int distance(const Pixel *p, const Pixel *q) {
    int dx = p->get_x() - q->get_x();
    int dy = p->get_y() - q->get_y();
    return std::sqrt(dx*dx + dy*dy);
}
