#ifndef OOP_BEHAVIOUR_H
#define OOP_BEHAVIOUR_H

#include "ObjectAttachment.h"

class Rigidbody;
class Collider;
class Shape;

class Behaviour : public ObjectAttachment {
protected:
    virtual void start() = 0;
    virtual void update(double deltaTime) = 0;

    virtual void onRigidbodyDestroy();
    virtual void onColliderDestroy();
    virtual void onShapeDestroy();
    virtual void onBehaviourDestroy(Behaviour*);

    virtual void onRigidbodyChange(Rigidbody* newRb);
    virtual void onColliderChange(Collider* newCollider);
    virtual void onShapeChange(Shape* newShape);
public:
    Behaviour();
    Behaviour(Behaviour const&) = delete;
    virtual ~Behaviour();
    Behaviour& operator=(Behaviour const&) = delete;

    virtual Behaviour* createCopy() = 0; ///creates and returns a pointer to a new identical object

    friend class Object;
};


#endif //OOP_BEHAVIOUR_H
