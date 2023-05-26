#include "Collider.h"
#include "CollisionHandler.h"
#include "Transform.h"
#include "appexceptions.h"

///constructors, copy assignment and destructor
Collider::Collider(Type t) : ObjectAttachment(), type(t) {
    CollisionHandler::getHandler().track(this);
}

Collider::Collider(Collider const& col) : ObjectAttachment(), type(col.type) {
    CollisionHandler::getHandler().track(this);
}

Collider& Collider::operator=(Collider const& col) { // cppcheck-suppress operatorEqVarError
    if(this==&col)
        return *this;
    type=col.type;
    return *this;
}

Collider::~Collider() {
    CollisionHandler::getHandler().untrack(this);
}

///setters
void Collider::setTransform(Transform *t) { transform=t; }
void Collider::setRigidbody(Rigidbody *rb) { rigidbody=rb; }

///getters
Vector const& Collider::getPosition() const {
    if(transform==nullptr)
        throw missing_reference("Collider", "getPosition()", "transform");
    return transform->getPosition();
}
double Collider::getRotation() const {
    if(transform==nullptr)
        throw missing_reference("Collider", "getRotation()", "transform");
    return transform->getRotation();
}

Transform& Collider::getTransform() const {
    if(transform==nullptr)
        throw missing_reference("Collider", "getTransform()", "transform");
    return *transform;
}

Rigidbody& Collider::getRigidbody() const {
    if(transform==nullptr)
        throw missing_reference("Collider", "getRigidbody()", "rigidbody");
    return *rigidbody;
}

Collider::Type Collider::getType() const { return type; }

bool Collider::getIsTrigger() const { return isTrigger; }

///setter
void Collider::setIsTrigger(bool tr) { isTrigger=tr; }