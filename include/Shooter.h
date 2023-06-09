#ifndef OOP_SHOOTER_H
#define OOP_SHOOTER_H

#include "Behaviour.h"
#include "ObjectData.h"

class Shooter : public Behaviour {
protected:
    ObjectData prefab;
    double speed;
    double cooldown;

    Transform* transform=nullptr;
    double timeSinceLastShot=0;

    void start() override;
    void update(double deltaTime) override;
public:
    Shooter(ObjectData const& prefab, double speed, double cooldown);
    Shooter(Shooter const& shooter);
    ~Shooter();

    Shooter()=delete;
    Shooter& operator=(Shooter const&)=delete;

    Behaviour* createCopy() override;
};


#endif //OOP_SHOOTER_H
