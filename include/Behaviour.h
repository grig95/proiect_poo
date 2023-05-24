#ifndef OOP_BEHAVIOUR_H
#define OOP_BEHAVIOUR_H

#include "ObjectAttachment.h"

class Behaviour : public ObjectAttachment {
protected:
    virtual void start() = 0;
    virtual void update(double deltaTime) = 0;

    virtual void onRigidbodyDestroy() = 0;
    virtual void onColliderDestroy() = 0;
    virtual void onShapeDestroy() = 0;
    virtual void onBehaviourDestroy(Behaviour* behaviour) = 0;
public:
    Behaviour();
    Behaviour(Behaviour const& b);
    virtual ~Behaviour();
    Behaviour& operator=(Behaviour const& b);

    virtual Behaviour* createCopy() = 0; ///creates and returns a pointer to a new identical object

    friend class Object;
};


#endif //OOP_BEHAVIOUR_H
