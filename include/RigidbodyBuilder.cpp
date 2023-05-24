#include "RigidbodyBuilder.h"

///constructor and destructor
RigidbodyBuilder::RigidbodyBuilder() = default;

RigidbodyBuilder::~RigidbodyBuilder() = default;

///build and reset
RigidbodyBuilder& RigidbodyBuilder::reset() {
    mass = 1;
    bounciness = 1;
    frictionCoefficient = 0;
    airDragCoefficient = 0;
    constraints = Rigidbody::Constraints::Free;
    return *this;
}

Rigidbody* RigidbodyBuilder::build() {
    return new Rigidbody(mass, bounciness, frictionCoefficient, airDragCoefficient, constraints);
}


///setters
RigidbodyBuilder& RigidbodyBuilder::setMass(double m) { mass=m; return *this; }
RigidbodyBuilder& RigidbodyBuilder::setBounciness(double b) { bounciness=b; return *this; }
RigidbodyBuilder& RigidbodyBuilder::setFrictionCoefficient(double f) { frictionCoefficient=f; return *this; }
RigidbodyBuilder& RigidbodyBuilder::setAirDragCoefficient(double d) { airDragCoefficient=d; return *this; }
RigidbodyBuilder& RigidbodyBuilder::setConstraints(Rigidbody::Constraints c) { constraints=c; return *this; }