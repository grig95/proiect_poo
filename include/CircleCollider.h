#ifndef OOP_CIRCLECOLLIDER_H
#define OOP_CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider {
private:
    double radius;
public:
    CircleCollider() = delete;
    CircleCollider(Transform* t, Rigidbody* rb, double const& radius=1);
    ~CircleCollider();
    CircleCollider& operator=(CircleCollider const& cc) = delete;
};


#endif //OOP_CIRCLECOLLIDER_H
