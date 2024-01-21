#include <iostream>
#include <stdexcept>
#include <cmath> 
class Vector;
class SymmetryLine;


class Point
{
public:
	Point() : x(0), y(0) {}
    Point(double a, double b) : x(a), y(b) {}
	
	void setX(double newX) { x = newX; }
	void setY(double newY) { y = newY; }
	double getX() const { return x; }
	double getY() const { return y; }
	void translation(Vector v);
	void rotation(double angle);
	void axial_symmetry(SymmetryLine line);
	void central_symmetry(Point a);
	
private:
	double x;
	double y;
};

class Vector
{ // vector that is placed at the origin
public:
	Vector() : x(0), y(0) {}
    Vector(double a, double b) : x(a), y(b) {}
    ~Vector() {}
    double getX() const { return x; }
    double getY() const { return y; }
	
private:
    double x;
    double y;

};

class SymmetryLine{
public:
	SymmetryLine(Point l, Point r) {left_point = l; right_point = r;}
	SymmetryLine(double left, double right, double top, double bottom)
	 : left_point(left, top), right_point(right, bottom) {}

	Point getLeft() const { return left_point; }
	Point getRight() const { return right_point; }
	
	bool if_vertical() const {return (right_point.getX() - left_point.getX()) == 0;}

	double getSlope() {
		if (!if_vertical()){ // to omit Devision by zero
        	return (right_point.getY() - left_point.getY()) / (right_point.getX() - left_point.getX());}
		else{return 0;}
    }

    double getYIntercept() {
        return left_point.getY() - getSlope() * left_point.getX();
    }
private:
	Point left_point;
	Point right_point;

};



class Line
{
public:
	// Function overloading (polymorphism)
	Line() : left_point(Point()), right_point(Point()) {}
	Line(Point l, Point r);
	Line(double left, double right, double top, double bottom);
	 //: left_point(left, top), right_point(right, bottom) {}
	~Line() {}

	void set_left_point(Point l) {left_point = l;}
	void set_right_point(Point r) {right_point = r;}

	void set_left_point(double x, double y);
	void set_right_point(double x, double y);

	Point getLeft() const { return left_point; }
	Point getRight() const { return right_point; }

	double length();
	bool if_belongs(Point a);

	void translation(Vector v);
	void rotation(double angle);
	void axial_symmetry(SymmetryLine line);
	void central_symmetry(Point a);

	//The functionality below is needed for if_belongs method

	bool if_vertical() const {return (right_point.getX() - left_point.getX()) == 0;}

	double getSlope() {
		if (!if_vertical()){ // We omit DIvisionByZero exeption if the line is vertical
        	return (right_point.getY() - left_point.getY()) / (right_point.getX() - left_point.getX());}
		else{return 0;}
    }

    double getYIntercept() {
        return left_point.getY() - getSlope() * left_point.getX();
    }
	

private:
	Point left_point;
	Point right_point;
};


class Triangle
{

public:
	Triangle(Point a, Point b, Point c);
	~Triangle() {}
	
	void set_point_1(Point l1)
	{point_1 = l1;
	 line1 = Line(l1, point_2);
	 line3 = Line(l1,point_3);}

	void set_point_2(Point l2)
	{point_2 = l2; 
	line2 = Line(l2, point_3);
	line1 = Line(point_1, l2);}

	void set_point_3(Point l3)
	{point_3 = l3; 
	line3 = Line(point_1,l3);
	line3 = Line(point_2,l3);}
	
	Point getPoint_1() const { return point_1; }
	Point getPoint_2() const { return point_2; }
	Point getPoint_3() const { return point_3; }

	Line getLine_1() const { return line1; }
	Line getLine_2() const { return line2; }
	Line getLine_3() const { return line3; }

	double area();
	double perimetr();
	bool lies_inside(Point a);
	void translation(Vector v);
	void rotation(double angle);
	void axial_symmetry(SymmetryLine line);
	void central_symmetry(Point a);

private:
	Point point_1;
	Point point_2;
	Point point_3;
	Line line1;
	Line line2;
	Line line3;


};


