#include "Shooter.h"
#include "Rigidbody.h"
#include "Object.h"

#include <iostream>

///constructors, destructor
Shooter::Shooter(ObjectData const& prefab, double speed, double cooldown) : Behaviour(), prefab(prefab), speed(speed), cooldown(cooldown) {}

Shooter::Shooter(Shooter const& shooter) : Behaviour(), prefab(shooter.prefab), speed(shooter.speed), cooldown(shooter.cooldown) {}

Shooter::~Shooter() = default;

///create copy
Behaviour* Shooter::createCopy() {
    return new Shooter(*this);
}

///start and update
void Shooter::start() {
    ///get transform
    transform=&getObject().getTransform();

    ///if prefab has no rigidbody, add a default one
    if(!prefab.hasRigidbody())
        prefab.setRigidbody(*(new Rigidbody()));
}

void Shooter::update(double deltaTime) {
    timeSinceLastShot+=deltaTime;

    if(transform == nullptr)
        std::cout<<"I'm a fraud!\n";

    if(timeSinceLastShot>=cooldown)
    {
        Object* projectile = new Object(prefab);
        projectile->getTransform()=*transform;
        projectile->getRigidbody().addForce(speed*transform->up(), Rigidbody::ForceMode::VelocityChange);
        timeSinceLastShot=0;
    }
}