#include "Transform.h"

///constructors, destructor, operators
Transform::Transform() : position(), rotation(0) {}

Transform::Transform(Transform const& t) = default;

Transform::Transform(const Vector &position, double rotation_rad) : position(position), rotation(clampAngleRad(rotation_rad)) {}

Transform::Transform(double pos_x, double pos_y, double rotation_rad) : position(pos_x, pos_y), rotation(rotation_rad) {}

Transform& Transform::operator=(Transform const& t) = default;

Transform::~Transform() = default;

bool Transform::operator==(Transform const& t) const { return position==t.position&&rotation==t.rotation; }

std::ostream& operator<<(std::ostream& os, Transform const& t) {
    os<<'('<<t.position<<", "<<t.rotation<<')';
    return os;
}

///functionality
void Transform::move(Vector const& v) { position+=v; }

void Transform::move(double move_x, double move_y) {
    position+=move_x*Vector::right()+move_y*Vector::up();
}

void Transform::rotate(double angle_rad) {
    rotation = clampAngleRad(rotation+angle_rad);
}

void Transform::rotateDeg(double angle_deg) {
    rotation = clampAngleRad(rotation+degToRad(angle_deg));
}

///utility
double Transform::degToRad(double angle) { return angle/180*std::numbers::pi; }

double Transform::radToDeg(double angle) { return angle/std::numbers::pi*180; }

double Transform::clampAngleRad(double angle) {
    return angle-std::floor(angle/std::numbers::pi/2)*std::numbers::pi*2;
}

double Transform::clampAngleDeg(double angle) {
    return angle-std::floor(angle/360)*360;
}

Vector Transform::up() const { return Vector(cos(rotation+std::numbers::pi/2), sin(rotation+std::numbers::pi/2)); }

Vector Transform::right() const { return Vector(cos(rotation), sin(rotation)); }

///getters, setters
Vector const& Transform::getPosition() const { return position; }

double Transform::getRotation() const { return rotation; }

double Transform::getRotationDeg() const { return radToDeg(rotation); }