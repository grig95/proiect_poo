#ifndef OOP_CIRCLECOLLIDER_H
#define OOP_CIRCLECOLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider {
private:
    double radius=1;
public:
    CircleCollider();
    CircleCollider(CircleCollider const& col);
    explicit CircleCollider(double radius);
    ~CircleCollider();
    CircleCollider& operator=(CircleCollider const& cc);

    Collider* createCopy() const override;

    double getRadius() const;

    friend class CollisionHandler;
};


#endif //OOP_CIRCLECOLLIDER_H
