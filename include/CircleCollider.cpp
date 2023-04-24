#include "CircleCollider.h"

///constructor and destructor

CircleCollider::CircleCollider(Transform* t, Rigidbody* rb, double const& radius) : Collider(t, rb), radius(radius) {}

CircleCollider::~CircleCollider() = default;