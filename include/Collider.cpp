#include "Collider.h"

///constructor and destructor
Collider::Collider(Transform* t, Rigidbody* rb) : transform(t), rigidbody(rb) {}

Collider::~Collider() = default;

///getters
Vector const& Collider::getPosition() const { return transform->getPosition(); }
double Collider::getRotation() const { return transform->getRotation(); }

//likely useless
Transform const& Collider::getTransform() const { return *transform; }
Rigidbody const& Collider::getRigidbody() const { return *rigidbody; }