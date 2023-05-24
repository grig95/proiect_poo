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
    Transform(Vector const& position, double rotation_rad);
    Transform(double pos_x, double pos_y, double rotation_rad);
    Transform& operator=(Transform const& t);
    ~Transform();

    bool operator==(Transform const& t) const;

    friend std::ostream& operator<<(std::ostream& os, Transform const& t);

    void setPosition(Vector const& pos);
    void move(Vector const& v);
    void move(double move_x, double move_y);
    void rotate(double angle_rad);
    void rotateDeg(double angle_deg);

    static double degToRad(double angle);
    static double radToDeg(double angle);
    static double clampAngleDeg(double angle);
    static double clampAngleRad(double angle);
    Vector up() const;
    Vector right() const;

    Vector const& getPosition() const;
    double getRotation() const;
    double getRotationDeg() const;

    ///friends
};


#endif //OOP_TRANSFORM_H
