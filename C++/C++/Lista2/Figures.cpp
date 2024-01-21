#include "Figures.hpp"

using std::cout;

double distance(Point a, Point b){
    double sum_1 = pow(a.getX() - b.getX(), 2);
	double sum_2 = pow(a.getY() - b.getY(), 2);
	return sqrt(sum_1 + sum_2);
};
bool if_parallel(Line a, Line b){
    double m1 = (a.getLeft().getY() - a.getRight().getY())/ (a.getLeft().getX() - a.getRight().getX());
    double m2 = (b.getLeft().getY() - b.getRight().getY())/ (b.getLeft().getX() - b.getRight().getX());
    if (m1 == m2){ return true;}
    else{return false;} 
};

bool if_perpendicular(Line a, Line b){
    double x_a = a.getRight().getX()-a.getLeft().getX();
    double y_a = a.getRight().getY()-a.getLeft().getY();
    double x_b = b.getRight().getX()-b.getLeft().getX();
    double y_b = b.getRight().getX()-b.getLeft().getX();

    double dotProduct = x_a*x_b+y_b*y_a;
    return (fabs(dotProduct) < 1e-9); // We do that to increase accuracy instead of checking if dotProduct==0
};



double my_area(Point a, Point b, Point c){
    double x1 = a.getX();
    double x2 = b.getX();
    double x3 = c.getX();

    double y1 = a.getY();
    double y2 = b.getY();
    double y3 = c.getY();

    return fabs(((x1*(y2-y1)) +(x2*(y3-y1)) + (x3*(y1-y2)))/2.0);
}

bool if_collinear(Point a, Point b, Point c){
   
    if (my_area(a,b,c)<= 1e-9){ return true;}
    else{ return false;}
}




// Point
void Point::translation(Vector v){
    x += v.getX();
    y += v.getY();
};
void Point::rotation(double angle)
{
    double radians = angle * M_PI / 180.0;
    double new_x = x * cos(radians) - y * sin(radians);
    double new_y = x * sin(radians) + y * cos(radians);
    x = new_x;
    y = new_y;
};

void Point::axial_symmetry(SymmetryLine line){
    if (line.if_vertical()) {
        double x_mirror = 2 * line.getLeft().getX() - x;
        setX(x_mirror);}
    else {
        double m = line.getSlope();
        double b = line.getYIntercept();
        double x_mirror = (x + (y - b) * m) / (m * m + 1);
        double y_mirror = b + m * (x_mirror - x);
        setX(2 * x_mirror - x);
        setY(2 * y_mirror - y);}
};

void Point::central_symmetry(Point a){
    double newX = 2*a.getX() - x;
    double newY = 2*a.getY() - y;
    setX(newX);
    setY(newY);
};

//Line

Line::Line(Point l, Point r){
    if ((l.getX() == r.getX()) and (l.getY() == r.getY())){
        throw std::invalid_argument("You cannot create a line with magnitude of 0");
    }
    left_point = l; right_point = r;
}
Line::Line(double left, double right, double top, double bottom){
    if ((left==right) and (top==bottom)){
        throw std::invalid_argument("You cannot create a line with magnitude of 0");
    }
    left_point.setX(left);
    left_point.setY(top);
    right_point.setX(right);
    right_point.setY(bottom);

}
double Line::length(){
    return distance(getLeft(), getRight());
}

bool Line::if_belongs(Point a){
    if (if_vertical()){
        return a.getX() == left_point.getX();
    }
    else{
        double slope = getSlope();
        double yIntercept = getYIntercept();
        double expected = slope * a.getX() + yIntercept;
        double actual = a.getY();
        if (fabs(expected - actual) < 1e-9) {
            return true;
        }
        else {
            return false;
        }
    }
}

void Line::translation(Vector v){
    left_point.translation(v);
    right_point.translation(v);
};

void Line::rotation(double angle){
    left_point.rotation(angle);
    right_point.rotation(angle);
};
void Line::axial_symmetry(SymmetryLine line){
    left_point.axial_symmetry(line);
    right_point.axial_symmetry(line);
}
void Line::central_symmetry(Point a){
    left_point.central_symmetry(a);
    left_point.central_symmetry(a);
}


// Triangle
Triangle::Triangle(Point a, Point b, Point c){
    
    if (if_collinear(a, b, c)){
        throw std::invalid_argument("Cannot create the triangle because all 3 point lie on the same line");
    }
    point_1 = a; point_2 = b; point_3 = c;
    line1 = Line(a,b);
    line2 = Line(b,c);
    line3 = Line(a,c);
};

double Triangle::area() {
    // Using Heron's formula to calculate area
    double a = line1.length();
    double b = line2.length();
    double c = line3.length();
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::perimetr(){
    return line1.length()+ line2.length() + line3.length();
}

void Triangle::translation(Vector v){
    point_1.translation(v);
    point_2.translation(v);
    point_3.translation(v);
};

void Triangle::rotation(double angle){
    point_1.rotation(angle);
    point_2.rotation(angle);
    point_3.rotation(angle);
};
void Triangle::axial_symmetry(SymmetryLine line){
    point_1.axial_symmetry(line);
    point_2.axial_symmetry(line);
    point_3.axial_symmetry(line);
}
void Triangle::central_symmetry(Point a){
    point_1.central_symmetry(a);
    point_2.central_symmetry(a);
    point_3.central_symmetry(a);
}




bool Triangle::lies_inside(Point p) {
    /*In this function I could've instantiate 3 objects of Triangle to have
    the access to area() method. However, if one of the triangle happens to be just a line
    then a constructor would throw an error (as intended). This would terminate the entire program.
    In order to omit this I calculate the area seperately for every triangle*/
        double area1 = 0.5 * abs(point_1.getX() * (point_2.getY() - p.getY()) +
                                      point_2.getX() * (p.getY() - point_1.getY()) +
                                      p.getX() * (point_1.getY() - point_2.getY()));
        double area2 = 0.5 * abs(point_2.getX() * (point_3.getY() - p.getY()) +
                                      point_3.getX() * (p.getY() - point_2.getY()) +
                                      p.getX() * (point_2.getY() - point_3.getY()));
        double area3 = 0.5 * abs(point_3.getX() * (point_1.getY() - p.getY()) +
                                      point_1.getX() * (p.getY() - point_3.getY()) +
                                      p.getX() * (point_3.getY() - point_1.getY()));
        double triangle_area = area();
        return (abs(triangle_area - area1 - area2 - area3) < 0.0001);
    }

bool if_disjoint(Triangle t1, Triangle t2){
    if (t1.lies_inside(t2.getPoint_1()) or t1.lies_inside(t2.getPoint_2()) or t1.lies_inside(t2.getPoint_3())
    or t2.lies_inside(t1.getPoint_1()) or t2.lies_inside(t1.getPoint_2()) or t2.lies_inside(t1.getPoint_3())){
        return false;
    }
    else{
        return false;
    }
}
bool if_one_lies_inside_another(Triangle t1, Triangle t2){
    if ((t1.lies_inside(t2.getPoint_1()) and t1.lies_inside(t2.getPoint_2()) and t1.lies_inside(t2.getPoint_3())) or
    (t2.lies_inside(t1.getPoint_1()) or t2.lies_inside(t1.getPoint_2()) or t2.lies_inside(t1.getPoint_3())) ){
        return true;
    }
    else{return false;}
}

int main(){
    // Testing Point class
    Point point_1(1, 2);
    Point point_2(1,2);
    Point point_3(1,2);
    Point point_4(1,2);
    Point point_5(1,2);
    Point point_6(1,2);

    Vector v(3, -1);
    point_1.translation(v);
    cout<<"Translation by vector v:"<<"\n";
    cout<<"("<<point_1.getX() << ',' << point_1.getY()<<")"<<"\n";

    point_2.rotation(90);
    cout<<"Rotation by 90 degrees:"<<"\n";
    cout<<"("<< point_2.getX() << ',' << point_2.getY()<<")"<<"\n";

    cout<<"Axial symmetry by vertical line x=3:"<<"\n";
    Point point_12(3, 2);
    Point point_22(3,42);
    SymmetryLine line1(point_12, point_22);
    point_3.axial_symmetry(line1);
    cout<<"("<< point_3.getX() << ',' << point_3.getY()<<")"<<"\n";

    cout<<"Axial symmetry by horizontal line y=0:"<<"\n";
    Point point_122(45, 0);
    Point point_222(42,0);
    SymmetryLine line2(point_122, point_222);
    point_4.axial_symmetry(line2);
    cout<<"("<< point_4.getX() << ',' << point_4.getY()<<")"<<"\n";


    cout<<"Axial symmetry by some line of the form y = mx + b:"<<"\n";
    Point point_1222(45, 4);
    Point point_2222(42,97);
    SymmetryLine line3(point_1222, point_2222);
    point_5.axial_symmetry(line3);
    cout<<"("<< point_5.getX() << ',' << point_5.getY()<<")"<<"\n";

    cout<<"The symmetric point of (3,4) about (1,2):"<<"\n";
    Point point_34(3,4);
    point_34.central_symmetry(point_6);
    cout<<"("<< point_34.getX() << ',' << point_34.getY()<<")"<<"\n";
    
    // Testing line

    //if_parallel
    cout<<"-------------------------------------"<<"\n";
    Line line_1(point_1, point_2);
    Line line_2(point_12, point_22);
    if (!if_parallel(line_1, line_2)){
        cout << "Not parallel"<<'\n';}
    else{ cout << "Parallel"<<'\n';}

    //if_perpendicular
    Point point_perp1(1,3);
    Point point_perp2(0,4);
    Point point_perp3(0,2);
    Point point_perp4(-2,0);
    Line line_12(point_perp1, point_perp2);
    Line line_22(point_perp3, point_perp4);
    if (!if_perpendicular(line_12, line_22)){
        cout << "Not perpendicular"<<'\n';}
    else{ cout << "Perpendicular"<<'\n';}

    //distance
    cout << "Length of line_22 is: "<<line_22.length()<<'\n';
    Point check_point(-6,-4);
    // if_belongs
    if (line_22.if_belongs(check_point)){
        cout<<"Yes, point (-6,-4) on line_22"<<"\n";
    }
    else{
        cout<<"Nope"<<"\n";
    }
    //Translation
    cout<<"Before the translation by vector (3,-1):"<<"\n";
    cout<<"("<< line_12.getLeft().getX() << ',' << line_12.getLeft().getY()<<")"<<" ";
    cout<<"("<< line_12.getRight().getX() << ',' << line_12.getRight().getY()<<")"<<"\n";
    line_12.translation(v);
    cout<<"After the translation by vector (3,-1):"<<"\n";
    cout<<"("<< line_12.getLeft().getX() << ',' << line_12.getLeft().getY()<<")"<<" ";
    cout<<"("<< line_12.getRight().getX() << ',' << line_12.getRight().getY()<<")"<<"\n";
    
    //Line bad_line(point_1, point_1); // will give an error

    // Triangle
    Point tr1(0,0);
    Point tr2(1,1);
    Point tr3(3,3);
    //Triangle bad_triangle(tr1,tr2,tr3); // would throw an error

    Point p1(3,0);
    Point p2(0,4);
    Point lp(1,1);
    Triangle triangle(tr1, p1, p2);
    cout<< "The area is: " << triangle.area()<<"\n";
    cout<< "The perimetr is: " << triangle.perimetr()<<"\n";
    //cout<<"If lies:"<<triangle.lies_inside(lp)<<"\n";
    cout<<"Point lies inside: "<<triangle.lies_inside(lp)<<"\n";
    
    // Testing if_disjoint
    Point g(1,0);
    Point t(0.5, 0.5);
    Triangle triag(tr1,g,t);
    cout<<"Checking if disjoint: "<<if_disjoint(triangle,triag)<<"\n";
    
    // Testing 

    



return 0;}