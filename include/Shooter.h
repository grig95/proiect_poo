#ifndef OOP_SHOOTER_H
#define OOP_SHOOTER_H

#include "Behaviour.h"
#include "ObjectData.h"

class Shooter : public Behaviour {
private:
    ObjectData prefab;
    double speed;
    double cooldown;

    Transform* transform=nullptr;
    double timeSinceLastShot=0;
public:
    Shooter(ObjectData const& prefab, double speed, double cooldown);
    Shooter(Shooter const& shooter);
    ~Shooter();

    Shooter()=delete;
    Shooter& operator=(Shooter const&)=delete;

    void start() override;
    void update(double deltaTime) override;

    Behaviour* createCopy() override;

    void onRigidbodyDestroy() override;
    void onColliderDestroy() override;
    void onShapeDestroy() override;
    void onBehaviourDestroy(Behaviour*) override;

    void onRigidbodyChange(Rigidbody&) override;
    void onColliderChange(Collider&) override;
    void onShapeChange(Shape&) override;
};


#endif //OOP_SHOOTER_H
