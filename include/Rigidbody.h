#ifndef OOP_RIGIDBODY_H
#define OOP_RIGIDBODY_H

#include "Transform.h"

class Rigidbody {
public:
    enum Constraints : char;
    enum ForceMode : char;
private:
    double mass;
    Transform *transform;
    Vector velocity;
    double angularVelocity; ///measured in RADIANS/s
    Constraints constraints;
    double bounciness;
    double frictionCoefficient;
    double airDragCoefficient; ///also takes into account the DENSITY of the fluid
    bool active;

    Vector resultantForce; ///sum of all forces applied between time steps
    double resultantAngularAcceleration; /// ????? (angular forces not implemented yet)
public:
    Rigidbody();
    Rigidbody(Rigidbody const& rb);
    Rigidbody(Transform const& t, double const& mass, Constraints const& c=(Constraints)0);
    Rigidbody(Transform const& t, double const& mass, double const& bounciness, double const& frictionCoefficient, double const& airDragCoefficient);
    Rigidbody(Vector const& position, double const& mass, Constraints const& c=(Constraints)0);
    Rigidbody(Vector const& position, double const& mass, double const& bounciness, double const& frictionCoefficient, double const& airDragCoefficient);
    ~Rigidbody();
    Rigidbody& operator=(Rigidbody const& rb);


    void step(double const& deltaTime);
    void addForce(Vector const& force, ForceMode forceMode=(ForceMode)1); ///default Force

    bool const& getActivation() const;
    void setActivation(bool a);

    Transform const& getTransform() const;
    Vector const& getPosition() const;
    double const& getRotation() const;

    Vector const& getVelocity() const;
    double const& getAngularVelocity() const;
    Vector const& getResultantForce() const;

    Constraints const& getConstraints() const;
    double const& getBounciness() const;
    double const& getFrictionCoefficient() const;
    double const& getAirDragCoefficient() const;

    void setConstraints(Constraints const& c);
    void setBounciness(double const& b);
    void setFrictionCoefficient(double const& f);
    void setAirDragCoefficient(double const& a);
};


#endif //OOP_RIGIDBODY_H
