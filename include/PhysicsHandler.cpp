#include "PhysicsHandler.h"
#include "Rigidbody.h"
#include "Collision.h"

#include <iostream> ///just for debugging

PhysicsHandler::PhysicsHandler() = default;
PhysicsHandler::~PhysicsHandler() = default;

PhysicsHandler& PhysicsHandler::getHandler() {
    static PhysicsHandler handler;
    return handler;
}

void PhysicsHandler::track(Rigidbody* rb) {
    if(rb==nullptr)
        return;
    rbodies.insert(rb);
}

void PhysicsHandler::untrack(Rigidbody* rb) {
    rbodies.erase(rb);
}

void PhysicsHandler::step(double deltaTime) {
    for(auto it=rbodies.begin();it!=rbodies.end();it++)
        if((*it)->isAttached())
            (*it)->step(deltaTime);
}

void PhysicsHandler::resolveCollision(const Collision &collision) {
    ///visual effect for testing
    std::cout<<"Collision detected!\n";
}