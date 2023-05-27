#ifndef OOP_RIGIDBODY_H
#define OOP_RIGIDBODY_H

#include "ObjectAttachment.h"
#include "Vector.h"

#include <cstdint>

class Transform;

class Rigidbody : public ObjectAttachment {
public:
    enum class Constraints : uint8_t {
        Free=0,
        FreezeX=1,
        FreezeY=2,
        FreezeRotation=4
    };
    enum class ForceMode : uint8_t {
        Force,
        Acceleration,
        Impulse,
        VelocityChange
    };
private:
    ///when changing any of the default values, don't forget to also change them in RigidbodyBuilder
    Transform* transform = nullptr;
    double mass = 1;
    Vector velocity = Vector::zero();
    double angularVelocity = 0; ///measured in RADIANS/s
    Constraints constraints = Constraints::Free;
    double bounciness = 1; ///fraction of energy turned to movement energy after impact
    double frictionCoefficient = 0; ///will be combined with the other rb's coefficient to create a collision coefficient
    double airDragCoefficient = 0; ///also takes into account the DENSITY of the fluid and the CROSS SECTIONAL AREA
    bool active = true;

    Vector resultantForce = Vector::zero(); ///sum of all forces applied between time steps
    Vector resultantImpulse = Vector::zero(); ///sum of all instantaneous forces (Impulse or VelocityChange)
    double resultantAngularAcceleration = 0; /// ????? (angular forces not implemented yet)

    void step(double deltaTime); ///meant to only be accessed by PhysicsHandler

    void setTransform(Transform* t); ///meant to only be accessed by Object
public:
    Rigidbody();
    Rigidbody(Rigidbody const& rb);
    explicit Rigidbody(double mass, Constraints const& c=Constraints::Free);
    Rigidbody(double mass, double bounciness, double frictionCoefficient, double airDragCoefficient, Constraints const& c=Constraints::Free);
    ~Rigidbody();
    Rigidbody& operator=(Rigidbody const& rb);

    void addForce(Vector const& force, ForceMode forceMode=ForceMode::Force);
    void addForceAtRelativePoint(Vector const& force, Vector const& relativePoint, ForceMode forceMode=ForceMode::Force);
    static double bouncinessCombinationFunction(double b1, double b2);
    static double frictionCoefficientCombinationFunction(double f1, double f2);

    bool const& getActivation() const;
    void setActivation(bool a);

    Transform& getTransform() const;
    Vector const& getPosition() const;
    double getRotation() const;

    Vector const& getVelocity() const;
    double getAngularVelocity() const;
    Vector const& getResultantForce() const;

    double getMass() const;
    Constraints const& getConstraints() const;
    double getBounciness() const;
    double getFrictionCoefficient() const;
    double getAirDragCoefficient() const;

    void setConstraints(Constraints const& c);
    void setBounciness(double b);
    void setFrictionCoefficient(double f);
    void setAirDragCoefficient(double a);

    friend class Object; ///meant to only access setTransform()
    friend class PhysicsHandler;
};


#endif //OOP_RIGIDBODY_H
