#include "Rigidbody.h"

///constructors, destructor, operators
Rigidbody::Rigidbody() : mass(1), velocity(), angularVelocity(0), constraints((Constraints)0), bounciness(1), frictionCoefficient(0), airDragCoefficient(0), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform();
}

Rigidbody::Rigidbody(Rigidbody const& rb) : mass(rb.mass), velocity(rb.velocity), angularVelocity(rb.angularVelocity), constraints(rb.constraints), bounciness(rb.bounciness), frictionCoefficient(rb.frictionCoefficient), airDragCoefficient(rb.airDragCoefficient), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform(*rb.transform);
}

Rigidbody::Rigidbody(Transform const& t, double const& mass, Constraints const& c) : mass(mass), velocity(), angularVelocity(0), constraints(c), bounciness(1), frictionCoefficient(0), airDragCoefficient(0), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform(t);
}

Rigidbody::Rigidbody(Vector const& position, double const& mass, Constraints const& c) : mass(mass), velocity(), angularVelocity(0), constraints(c), bounciness(1), frictionCoefficient(0), airDragCoefficient(0), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform(position, 0);
}

Rigidbody::Rigidbody(Transform const& t, double const& mass, double const& bounciness, double const& frictionCoefficient, double const& airDragCoefficient) : mass(mass), velocity(), angularVelocity(0), constraints((Constraints)0), bounciness(bounciness), frictionCoefficient(frictionCoefficient), airDragCoefficient(airDragCoefficient), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform(t);
}

Rigidbody::Rigidbody(Vector const& position, double const& mass, double const& bounciness, double const& frictionCoefficient, double const& airDragCoefficient) : mass(mass), velocity(), angularVelocity(0), constraints((Constraints)0), bounciness(bounciness), frictionCoefficient(frictionCoefficient), airDragCoefficient(airDragCoefficient), active(true), resultantForce(), resultantAngularAcceleration(0) {
    transform=new Transform(position, 0);
}

Rigidbody& Rigidbody::operator=(Rigidbody const& rb) {
    mass=rb.mass;
    transform=new Transform(*rb.transform);
    velocity=rb.velocity;
    angularVelocity=rb.angularVelocity;
    constraints=rb.constraints;
    bounciness=rb.bounciness;
    frictionCoefficient=rb.frictionCoefficient;
    airDragCoefficient=rb.airDragCoefficient;
    active=rb.active;

    ///?
    resultantForce=rb.resultantForce;
    resultantAngularAcceleration=rb.resultantAngularAcceleration;

    return *this;
}

Rigidbody::~Rigidbody() = default;

///functionality
enum Rigidbody::Constraints : char {
    FreezeX=1,
    FreezeY=2,
    FreezeRotation=4
};

enum Rigidbody::ForceMode : char {
    Force=1,
    Acceleration=2
};

void Rigidbody::step(double const& deltaTime) {
    if(!active)
        return;

    ///position side
    velocity+=resultantForce*deltaTime/mass;
    velocity-=velocity.normalized()*pow(velocity.magnitude(), 2)*airDragCoefficient*deltaTime;
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