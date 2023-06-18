#include "ObjectHandler.h"
#include "Object.h"

#include "Averager.h"

///basics
ObjectHandler::ObjectHandler() = default;
ObjectHandler::~ObjectHandler() = default;

ObjectHandler& ObjectHandler::getHandler() {
    static ObjectHandler handler;
    return handler;
}


///control methods
void ObjectHandler::track(Object* obj) {
    if(obj==nullptr)
        return;
    objects.insert(obj);
}

void ObjectHandler::untrack(Object* obj) {
    if(obj==nullptr)
        return;
    objects.erase(obj);
}


///functionality
void ObjectHandler::render(sf::RenderWindow& window) const {
    for(auto it=objects.begin();it!=objects.end();it++)
        (*it)->render(window);
}

void ObjectHandler::update(double deltaTime) const {
    for(auto it=objects.begin();it!=objects.end();it++)
        (*it)->update(deltaTime);
}


///average thing
Vector ObjectHandler::getAveragePosition() {
    Averager<Vector> avg;

    for(auto it=objects.begin();it!=objects.end();it++)
        avg.add((*it)->getTransform().getPosition());

    return avg.getAverage();
}