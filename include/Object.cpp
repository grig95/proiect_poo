#include "Object.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "appexceptions.h"
#include "ObjectHandler.h"
#include "Shape.h"

///basics
Object::Object() : transform(), behaviours() {
    ObjectHandler::getHandler().track(this);
}

Object::~Object() {
    if(rigidbody!=nullptr)
        delete rigidbody;
    if(collider!=nullptr)
        delete collider;
    if(shape!=nullptr)
        delete shape;
    for(unsigned int i=0;i<behaviours.size();i++)
        delete behaviours[i];

    ObjectHandler::getHandler().untrack(this);
}

Object::Object(Object const& obj) : transform(obj.transform), behaviours() {
    if(obj.rigidbody!=nullptr)
    {
        rigidbody=new Rigidbody(*obj.rigidbody);
        rigidbody->attachTo(this);
        rigidbody->setTransform(&transform);
    }
    if(obj.collider!=nullptr)
    {
        collider=obj.collider->createCopy();
        collider->attachTo(this);
        collider->setTransform(&transform);
        if(rigidbody!=nullptr)
            collider->setRigidbody(rigidbody);
    }

    if(obj.shape!=nullptr)
    {
        shape=new Shape(*obj.shape);
        shape->attachTo(this);
        shape->setTransform(&transform);
    }

    for(unsigned int i=0;i<obj.behaviours.size();i++)
    {
        behaviours.push_back(obj.behaviours[i]->createCopy());
        behaviours[i]->attachTo(this);
        behaviours[i]->start();
    }

    ObjectHandler::getHandler().track(this);
}

///functionality
void Object::render(sf::RenderWindow& window) const {
    if(shape==nullptr)
        return;
    shape->render(window);
}

void Object::update(double deltaTime) {
    for(unsigned int i=0;i<behaviours.size();i++)
        behaviours[i]->update(deltaTime);
}


///attachers
void Object::attachRigidbody(Rigidbody &rb) {
    if(rb.isAttached())
        throw unique_bind_error("Object", "Rigidbody");

    rb.attachTo(this);
    rb.setTransform(&transform);
    rigidbody=&rb;

    if(collider!=nullptr)
        collider->setRigidbody(rigidbody);
}

void Object::attachCollider(Collider &col) {
   if(col.isAttached())
       throw unique_bind_error("Object", "Collider");

   col.attachTo(this);
   col.setTransform(&transform);
   if(rigidbody!=nullptr)
       col.setRigidbody(rigidbody);
   collider=&col;
}

void Object::attachShape(Shape& sh) {
    shape=&sh;
    shape->setTransform(&transform);
}

void Object::attachBehaviour(Behaviour &behaviour) {
    if(behaviour.isAttached())
        throw unique_bind_error("Object", "Behaviour");

    behaviour.attachTo(this);
    behaviours.push_back(&behaviour);
    behaviour.start();
}

///checkers
bool Object::hasRigidbody() { return rigidbody!=nullptr; }
bool Object::hasCollider() { return collider!=nullptr; }
bool Object::hasShape() { return shape!=nullptr; }

///detachers
void Object::destroyRigidbody() {
    if(rigidbody==nullptr)
        return;
    delete rigidbody;
    rigidbody=nullptr;
    if(collider!=nullptr)
        collider->setRigidbody(nullptr);

    for(unsigned int i=0;i<behaviours.size();i++)
        behaviours[i]->onRigidbodyDestroy();
}

void Object::destroyCollider() {
    if(collider==nullptr)
        return;
    delete collider;
    collider=nullptr;

    for(unsigned int i=0;i<behaviours.size();i++)
        behaviours[i]->onColliderDestroy();
}

void Object::destroyShape() {
    if(shape==nullptr)
        return;
    delete shape;
    shape=nullptr;

    for(unsigned int i=0;i<behaviours.size();i++)
        behaviours[i]->onShapeDestroy();
}


///getters
Transform& Object::getTransform() { return transform; }
Vector const& Object::getPosition() const { return transform.getPosition(); }
double Object::getRotation() const { return transform.getRotation(); }

Rigidbody& Object::getRigidbody() const {
    if(rigidbody==nullptr)
        throw missing_reference("Object", "getRigidbody()", "rigidbody");
    return *rigidbody;
}

Collider& Object::getCollider() const {
    if(collider==nullptr)
        throw missing_reference("Object", "getCollider()", "collider");
    return *collider;
}

Shape& Object::getShape() const {
    if(shape==nullptr)
        throw missing_reference("Object", "getShape()", "shape");
    return *shape;
}