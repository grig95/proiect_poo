#include "Rigidbody.h"
#include "appexceptions.h"
#include "Vector.h"
#include "Transform.h"
#include "PhysicsHandler.h"

///constructors, destructor, operators
Rigidbody::Rigidbody() : ObjectAttachment() {
    PhysicsHandler::getHandler().track(this);
}

Rigidbody::Rigidbody(Rigidbody const& rb) : ObjectAttachment(), transform(nullptr), mass(rb.mass), bounciness(rb.bounciness), frictionCoefficient(rb.frictionCoefficient), airDragCoefficient(rb.airDragCoefficient), active(rb.active) {
    PhysicsHandler::getHandler().track(this);
}

Rigidbody::Rigidbody(double mass, Constraints const& c) : ObjectAttachment(), mass(mass), constraints(c) {
    PhysicsHandler::getHandler().track(this);
}

Rigidbody::Rigidbody(double mass, double bounciness, double frictionCoefficient, double airDragCoefficient, Constraints const& c) : ObjectAttachment(), mass(mass), constraints(c), bounciness(bounciness), frictionCoefficient(frictionCoefficient), airDragCoefficient(airDragCoefficient) {
    PhysicsHandler::getHandler().track(this);
}


Rigidbody& Rigidbody::operator=(Rigidbody const& rb) { // cppcheck-suppress operatorEqVarError
    if(this==&rb)
        return *this;

    mass=rb.mass;
    velocity=rb.velocity;
    constraints=rb.constraints;
    bounciness=rb.bounciness;
    frictionCoefficient=rb.frictionCoefficient;
    airDragCoefficient=rb.airDragCoefficient;
    active=rb.active;

    return *this;
}

Rigidbody::~Rigidbody() {
    PhysicsHandler::getHandler().untrack(this);
}

///functionality
void Rigidbody::step(double deltaTime) {
    if(transform==nullptr)
        return;
    if(!active)
        return;

    ///position side
    velocity+=resultantForce*deltaTime/mass;
    velocity+=resultantImpulse/mass;

    Vector oldDirection=velocity.normalized();
    velocity-=velocity.normalized()*pow(velocity.magnitude(), 2)*airDragCoefficient*deltaTime/mass/2;
    if((oldDirection.getX()>0&&velocity.getX()<0) || (oldDirection.getX()<0&&velocity.getX()>0))
        velocity-=Vector::right()*velocity.getX();
    if((oldDirection.getY()>0&&velocity.getY()<0) || (oldDirection.getY()<0&&velocity.getY()>0))
        velocity-=Vector::up()*velocity.getY();


    transform->move(velocity*deltaTime);
    resultantForce=Vector::zero();
    resultantImpulse=Vector::zero();

    ///angular side
    //air drag angular slow-down (?????)
    transform->rotate(angularVelocity*deltaTime);
}

void Rigidbody::addForce(Vector const& force, ForceMode forceMode) {
    if(transform==nullptr)
        return;
    if(!active)
        return;

    switch(forceMode) {
        case ForceMode::Force:
            resultantForce+=force;
            break;
        case ForceMode::Acceleration:
            resultantForce+=force*mass;
            break;
        case ForceMode::Impulse:
            resultantImpulse+=force;
            break;
        case ForceMode::VelocityChange:
            resultantImpulse+=force*mass;
            break;
    }
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

Transform& Rigidbody::getTransform() const {
    if(transform==nullptr)
        throw missing_reference("Rigidbody", "getTransform()", "transform");
    return *transform;
}
Vector const& Rigidbody::getPosition() const {
    if(transform==nullptr)
        throw missing_reference("Rigidbody", "getPosition()", "transform");
    return transform->getPosition();
}
double Rigidbody::getRotation() const {
    if(transform==nullptr)
        throw missing_reference("Rigidbody", "getRotation()", "transform");
    return transform->getRotation();
}

Vector const& Rigidbody::getVelocity() const { return velocity; }
double Rigidbody::getAngularVelocity() const { return angularVelocity; }
Vector const& Rigidbody::getResultantForce() const { return resultantForce; }

Rigidbody::Constraints const& Rigidbody::getConstraints() const { return constraints; }
double Rigidbody::getBounciness() const { return bounciness; }
double Rigidbody::getFrictionCoefficient() const { return frictionCoefficient; }
double Rigidbody::getAirDragCoefficient() const { return airDragCoefficient; }

void Rigidbody::setTransform(Transform *t) { transform = t; }
void Rigidbody::setConstraints(Constraints const& c) { constraints=c; }
void Rigidbody::setBounciness(double b) { bounciness=b; }
void Rigidbody::setFrictionCoefficient(double f) { frictionCoefficient=f; }
void Rigidbody::setAirDragCoefficient(double a) { airDragCoefficient=a; }