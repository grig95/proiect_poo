#include "CircleCollider.h"

///constructos, copy assignment and destructor
CircleCollider::CircleCollider() : Collider(Type::CircleCollider) {}

CircleCollider::CircleCollider(CircleCollider const& col) : Collider(col), radius(col.radius) {}

CircleCollider::CircleCollider(double radius) : Collider(Type::CircleCollider), radius(radius) {}

CircleCollider::~CircleCollider() = default;

CircleCollider& CircleCollider::operator=(CircleCollider const& col) = default;

///abstract copy
Collider* CircleCollider::createCopy() const {
    return new CircleCollider(*this);
}

///getter
double CircleCollider::getRadius() const { return radius; }