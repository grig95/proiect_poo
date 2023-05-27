#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H

#include <fstream>
#include <cmath>

class Vector {
private:
    double x;
    double y;
public:
    Vector();
    Vector(Vector const &v);
    Vector(double x, double y);
    Vector& operator=(Vector const &v);
    ~Vector();

    Vector operator+(Vector const &v) const;
    Vector operator-(Vector const &v) const;
    Vector operator-() const;
    Vector operator*(double s) const;
    friend Vector operator*(double s, Vector const &v);
    Vector& operator+=(Vector const &v);
    Vector& operator-=(Vector const &v);
    Vector& operator*=(double s);
    Vector operator/(double s) const;
    Vector& operator/=(double s);

    bool operator==(Vector const& v) const;

    friend std::ostream& operator<<(std::ostream& o, Vector const& v);

    double magnitude() const;
    Vector normalized() const;

    static Vector const& up();
    static Vector const& right();
    static Vector const& zero();

    void setX(double x);
    void setY(double y);

    double getX() const;
    double getY() const;

    ///friends
};


#endif //OOP_VECTOR_H
