#include "Figures.hpp"
using std::cout;

class Rectangle
{
public:
	Rectangle(int newTop, int newLeft, int newBottom, int newRight);
	~Rectangle() {}
	
	int getTop() const { return top; }
	int getLeft() const { return left; }
	int getBottom() const { return bottom; }
	int getRight() const { return right; }

	Point getUpperLeft() const { return upperLeft; }
	Point getLowerLeft() const { return lowerLeft; }
	Point getUpperRight() const { return upperRight; }
	Point getLowerRight() const { return lowerRight; }

	void setUpperLeft(Point location);
	void setLowerLeft(Point location);
	void setUpperRight(Point location);
	void setLowerRight(Point location);

	void setTop(int newTop);
	void setLeft(int newLeft);
	void setBottom(int newBottom);
	void setRight(int newRight);

	int getArea() const;

private:
	Point upperLeft;
	Point upperRight;
	Point lowerLeft;
	Point lowerRight;
	int top;
	int left;
	int bottom;
	int right;
};
Rectangle::Rectangle(int newTop, int newLeft, int newBottom, int newRight)
{
	top = newTop;
	left = newLeft;
	bottom = newBottom;
	right = newRight;

	upperLeft.setX(left);
	upperLeft.setY(top);

	upperRight.setX(right);
	upperRight.setY(top);

	lowerLeft.setX(left);
	lowerLeft.setY(bottom);

	lowerRight.setX(right);
	lowerRight.setY(bottom);
}

void Rectangle::setUpperLeft(Point location)
{
	upperLeft = location;
    upperRight.setY(location.getY());
    lowerLeft.setX(location.getX());
    top = location.getY();
    left = location.getX();
}

void Rectangle::setLowerLeft(Point location)
{
	lowerLeft = location;
	lowerRight.setY(location.getY());
	upperLeft.setX(location.getX());
	bottom = location.getY();
	left = location.getX();
}

void Rectangle::setLowerRight(Point location)
{
	lowerRight = location;
	lowerLeft.setY(location.getY());
	upperRight.setX(location.getX());
	bottom = location.getY();
	right = location.getX();
}

void Rectangle::setUpperRight(Point location)
{
	upperRight = location;
	upperLeft.setY(location.getY());
	lowerRight.setX(location.getX());
	top = location.getY();
	right = location.getX();
}

void Rectangle::setTop(int newTop)
{
	top = newTop;
	upperLeft.setY(top);
	upperRight.setY(top);
}

void Rectangle::setLeft(int newLeft)
{
	left = newLeft;
	upperLeft.setX(left);
	lowerLeft.setX(left);
}

void Rectangle::setBottom(int newBottom)
{
	bottom = newBottom;
	lowerLeft.setY(bottom);
	lowerRight.setY(bottom);
}

void Rectangle::setRight(int newRight)
{
	right = newRight;
	upperRight.setX(right);
}

// find width and height from corners then multiply for area 
int Rectangle::getArea() const
{
	int width = right - left;
	int height = top - bottom;
	return (width * height);
}

int main()
{
	// initialize a local Rectangle variable
	Rectangle myRectangle(100, 20, 50, 80);
	
	int area = myRectangle.getArea();

	cout << "Area: " << area << "\n";
	cout << "Upper Left X Coordinate: ";
	cout << myRectangle.getUpperLeft().getX() << "\n";
	return 0;
}
