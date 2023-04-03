#ifndef OOP_TRANSFORM_H
#define OOP_TRANSFORM_H

#include "Vector.h"
#include <numbers>

class Transform {
private:
    Vector position;
    double rotation; ///measured in RADIANS
public:
    Transform();
    Transform(Transform const& t);
    Transform(Vector const& position, double const& rotation_rad);
    Transform(double const& pos_x, double const& pos_y, double const& rotation_rad);
    Transform& operator=(Transform const& t);
    ~Transform();

    bool operator==(Transform const& t) const;

    friend std::ostream& operator<<(std::ostream& os, Transform const& t);

    void move(Vector const& v);
    void move(double const& move_x, double const& move_y);
    void rotate(double const& angle_rad);
    void rotateDeg(double const& angle_deg);

    static double degToRad(double const& angle);
    static double radToDeg(double const& angle);
    static double clampAngleDeg(double const& angle);
    static double clampAngleRad(double const& angle);
    Vector up() const;
    Vector right() const;

    Vector const& getPosition() const;
    double const& getRotation() const;
    double getRotationDeg() const;

    ///friends
};


#endif //OOP_TRANSFORM_H
