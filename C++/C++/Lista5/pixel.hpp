
class Pixel
{
public:
    static std::string RESOLUTION;
    static int HEIGHT;
    static int WIDTH;
    Pixel() : x(0), y(0) {}
    Pixel(int a, int b)
    {
        if (x < 0 || x > WIDTH || b < 0 || HEIGHT > 255)
        {
            throw std::invalid_argument("Invalid value");
        }
        x = a;
        y = b;
    }

    int get_x() const
    {
        return x;
    }
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
            throw std::out_of_range("Pixel is out the screen");
        }
        set_x(new_x);
        set_y(new_y);
    }
};
