#include "PhysicsHandler.h"
#include "Rigidbody.h"

///debugging only
#include <iostream>
#include "Object.h"
#include "Shape.h"

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