#ifndef OOP_RIGIDBODYBUILDER_H
#define OOP_RIGIDBODYBUILDER_H

#include "Rigidbody.h"

class RigidbodyBuilder {
private:
    ///if default values are ever changed, modify them in clear() as well
    double mass = 1;
    double bounciness = 1;
    double frictionCoefficient = 0;
    double airDragCoefficient = 0;
    Rigidbody::Constraints constraints = Rigidbody::Constraints::Free;
public:
    RigidbodyBuilder();
    ~RigidbodyBuilder();

    RigidbodyBuilder(RigidbodyBuilder const&) = delete;
    RigidbodyBuilder& operator=(RigidbodyBuilder const&) = delete;

    RigidbodyBuilder& reset();
    RigidbodyBuilder& setMass(double m);
    RigidbodyBuilder& setBounciness(double b);
    RigidbodyBuilder& setFrictionCoefficient(double f);
    RigidbodyBuilder& setAirDragCoefficient(double d);
    RigidbodyBuilder& setConstraints(Rigidbody::Constraints c);
    Rigidbody* build();

};


#endif //OOP_RIGIDBODYBUILDER_H
