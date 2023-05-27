#include "Rotator.h"
#include "Object.h"

///basics
Rotator::Rotator(double rotationSpeed) : rotationSpeed(rotationSpeed) {}

Rotator::Rotator(Rotator const& rotator) : rotationSpeed(rotator.rotationSpeed) {}

Rotator& Rotator::operator=(Rotator const& rotator) {
    if(this==&rotator)
        return *this;

    rotationSpeed=rotator.rotationSpeed;
    return *this;
}

Rotator::~Rotator() = default;

///start and update
void Rotator::start() {
    transform=&getObject().getTransform();
}

void Rotator::update(double deltaTime) {
    transform->rotate(rotationSpeed*deltaTime);
}


///createCopy()
Behaviour* Rotator::createCopy() { return new Rotator(*this); }


///onDestroy()s
void Rotator::onRigidbodyDestroy() {}
void Rotator::onColliderDestroy() {}
void Rotator::onShapeDestroy() {}
void Rotator::onBehaviourDestroy(Behaviour*) {}


///onChange()s
void Rotator::onRigidbodyChange(Rigidbody&) {}
void Rotator::onColliderChange(Collider&) {}
void Rotator::onShapeChange(Shape&) {}