#include "Rigidbody.h"

///constructors, destructor, operators
Rigidbody::Rigidbody(Transform* t) : transform(t), mass(1), velocity(), angularVelocity(0), constraints((Constraints)0), bounciness(1), frictionCoefficient(0), airDragCoefficient(0), active(true), resultantForce(), resultantAngularAcceleration(0) {}

Rigidbody::Rigidbody(Transform* t, double const& mass, Constraints const& c) : transform(t), mass(mass), velocity(), angularVelocity(0), constraints(c), bounciness(1), frictionCoefficient(0), airDragCoefficient(0), active(true), resultantForce(), resultantAngularAcceleration(0) {}

Rigidbody::Rigidbody(Transform* t, double const& mass, double const& bounciness, double const& frictionCoefficient, double const& airDragCoefficient) : transform(t), mass(mass), velocity(), angularVelocity(0), constraints((Constraints)0), bounciness(bounciness), frictionCoefficient(frictionCoefficient), airDragCoefficient(airDragCoefficient), active(true), resultantForce(), resultantAngularAcceleration(0) {}

Rigidbody& Rigidbody::operator=(Rigidbody const& rb) {
    if(this==&rb)
        return *this;

    mass=rb.mass;
    velocity=rb.velocity;
    angularVelocity=rb.angularVelocity;
    constraints=rb.constraints;
    bounciness=rb.bounciness;
    frictionCoefficient=rb.frictionCoefficient;
    airDragCoefficient=rb.airDragCoefficient;
    active=rb.active;

    return *this;
}

Rigidbody::~Rigidbody() = default;

///functionality
enum Rigidbody::Constraints : uint8_t {
    FreezeX=1,
    FreezeY=2,
    FreezeRotation=4
};

enum Rigidbody::ForceMode : uint8_t {
    Force=1,
    Acceleration=2
};

void Rigidbody::step(double const& deltaTime) {
    if(!active)
        return;

    ///position side
    velocity+=resultantForce*deltaTime/mass;
    velocity-=velocity.normalized()*pow(velocity.magnitude(), 2)*airDragCoefficient*deltaTime/mass;
    if(velocity.getX()<0)
        velocity-=Vector::right()*velocity.getX();
    if(velocity.getY()<0)
        velocity-=Vector::up()*velocity.getY();
    transform->move(velocity*deltaTime);
    resultantForce=Vector::zero();

    ///angular side
    //air drag angular slow-down (?????)
    transform->rotate(angularVelocity*deltaTime);
}

void Rigidbody::addForce(Vector const& force, ForceMode forceMode) {
    if(!active)
        return;

    if(forceMode==ForceMode::Force)
        resultantForce+=force;
    else if(forceMode==ForceMode::Acceleration)
        resultantForce+=force*mass;
}

///utility

///getters, setters
bool const& Rigidbody::getActivation() const { return active; }
void Rigidbody::setActivation(bool a) {
    active=a;
    if(!a)
    {
        resultantForce=Vector::zero();
        velocity=Vector::zero();
        angularVelocity=0;
        resultantAngularAcceleration=0;
    }
}

Transform const& Rigidbody::getTransform() const { return *transform; }
Vector const& Rigidbody::getPosition() const { return transform->getPosition(); }
double const& Rigidbody::getRotation() const { return transform->getRotation(); }

Vector const& Rigidbody::getVelocity() const { return velocity; }
double const& Rigidbody::getAngularVelocity() const { return angularVelocity; }
Vector const& Rigidbody::getResultantForce() const { return resultantForce; }

Rigidbody::Constraints const& Rigidbody::getConstraints() const { return constraints; }
double const& Rigidbody::getBounciness() const { return bounciness; }
double const& Rigidbody::getFrictionCoefficient() const { return frictionCoefficient; }
double const& Rigidbody::getAirDragCoefficient() const { return airDragCoefficient; }

void Rigidbody::setConstraints(Constraints const& c) { constraints=c; }
void Rigidbody::setBounciness(double const& b) { bounciness=b; }
void Rigidbody::setFrictionCoefficient(double const& f) { frictionCoefficient=f; }
void Rigidbody::setAirDragCoefficient(double const& a) { airDragCoefficient=a; }