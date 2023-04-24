#ifndef OOP_CIRCLECOLLIDER_H
#define OOP_CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider {
private:
    double radius;
public:
    CircleCollider() = delete;
    CircleCollider(Transform* t, Rigidbody* rb, double radius=1);
    ~CircleCollider();
    CircleCollider& operator=(CircleCollider const& cc) = delete;

    double getRadius() const;
};


#endif //OOP_CIRCLECOLLIDER_H
