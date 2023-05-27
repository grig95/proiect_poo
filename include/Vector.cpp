#include "Vector.h"

///constructors, destructor, operators
Vector::Vector() : x(0), y(0) {}

Vector::Vector(Vector const &v) = default;

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector& Vector::operator=(Vector const &v) = default;

Vector::~Vector() = default;

Vector Vector::operator+(Vector const &v) const {
    Vector vn(*this);
    vn.x+=v.x;
    vn.y+=v.y;
    return vn;
}

Vector Vector::operator-(Vector const &v) const {
    Vector vn(*this);
    vn.x-=v.x;
    vn.y-=v.y;
    return vn;
}

Vector Vector::operator-() const {
    return {-x, -y};
}

Vector Vector::operator*(double s) const {
    Vector vn(*this);
    vn.x*=s;
    vn.y*=s;
    return vn;
}

Vector operator*(double s, Vector const &v) {
    Vector vn(v);
    vn.x*=s;
    vn.y*=s;
    return vn;
}

Vector& Vector::operator+=(Vector const& v) {
    x+=v.x;
    y+=v.y;
    return *this;
}

Vector& Vector::operator-=(Vector const& v) {
    x-=v.x;
    y-=v.y;
    return *this;
}

Vector& Vector::operator*=(double s) {
    x*=s;
    y*=s;
    return *this;
}

Vector Vector::operator/(double s) const {
    Vector vn(*this);
    vn.x/=s;
    vn.y/=s;
    return vn;
}

Vector& Vector::operator/=(double s) {
    x/=s;
    y/=s;
    return *this;
}

bool Vector::operator==(Vector const& v) const { return x==v.x&&y==v.y; }

std::ostream& operator<<(std::ostream& os, Vector const& v) {
    os<<'('<<v.x<<", "<<v.y<<")";
    return os;
}

///functionality
double Vector::magnitude() const { return sqrt(x*x+y*y); }

Vector Vector::normalized() const {
    double m=magnitude();
    if(m==0)
        return zero();
    return Vector(x/m, y/m);
}

///utility
Vector const& Vector::up() {
    static Vector const v(0, 1);
    return v;
}

Vector const& Vector::right() {
    static Vector const v(1, 0);
    return v;
}

Vector const& Vector::zero() {
    static Vector const v(0, 0);
    return v;
}


///getters, setters
void Vector::setX(double newX) { x=newX; }
void Vector::setY(double newY) { y=newY; }

double Vector::getX() const { return x; }
double Vector::getY() const { return y; }