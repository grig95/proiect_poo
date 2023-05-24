#ifndef OOP_COLLISION_H
#define OOP_COLLISION_H

#include "Vector.h"
#include "Transform.h"

class Collider;

class Collision {
private:
    double timeElapsed;
    Vector contactPoint;
    Collider& col1;
    Collider& col2;
    Transform transform1, transform2; ///transforms at first contact time
    Vector normal1, normal2;
public:
    Collision() = delete;
    Collision(Collision const& collision);
    Collision(double timeElapsed, Vector const& contactPoint, Collider& col1, Collider& col2, Transform const& t1, Transform const& t2, Vector const& normal1, Vector const& normal2);
    Collision& operator=(Collision const&) = delete;
    Collision& operator=(Collision&&) = delete;
    ~Collision();

    double getTimeElapsed() const;
    Vector const& getContactPoint() const;
    Collider& getCol1() const;
    Collider& getCol2() const;
    Transform const& getTransform1() const;
    Transform const& getTransform2() const;
    Vector const& getNormal1() const;
    Vector const& getNormal2() const;
};


#endif //OOP_COLLISION_H
