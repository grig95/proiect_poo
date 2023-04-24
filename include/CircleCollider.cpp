#include "CircleCollider.h"

///constructor and destructor

CircleCollider::CircleCollider(Transform* t, Rigidbody* rb, double radius) : Collider(t, rb), radius(radius) {}

CircleCollider::~CircleCollider() = default;

///getter
double CircleCollider::getRadius() const { return radius; }