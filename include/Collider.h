#ifndef OOP_COLLIDER_H
#define OOP_COLLIDER_H

#include "Rigidbody.h"

class Collider {
protected:
    Transform* transform;
    Rigidbody* rigidbody;
public:
    Collider() = delete;
    Collider(Transform* t, Rigidbody* rb);
    ~Collider();
    Collider& operator=(Collider const& col) = delete;

    Transform const& getTransform() const;
    Rigidbody const& getRigidbody() const;
};


#endif //OOP_COLLIDER_H
