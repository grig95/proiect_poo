#include "ObjectData.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Shape.h"
#include "Behaviour.h"
#include "Object.h"


///basics
ObjectData::ObjectData() : transform() {}

ObjectData::ObjectData(Object const& obj) : transform(obj.transform) {
    if(obj.rigidbody!=nullptr)
        rigidbody=new Rigidbody(*obj.rigidbody);
    if(obj.collider!=nullptr)
        collider=obj.collider->createCopy();
    if(obj.shape!=nullptr)
        shape=new Shape(*obj.shape);
    for(unsigned int i=0;i<obj.behaviours.size();i++)
        behaviours.push_back(obj.behaviours[i]->createCopy());
}

ObjectData::ObjectData(ObjectData const& obd) : transform(obd.transform) {
    if(obd.rigidbody != nullptr)
        rigidbody=new Rigidbody(*obd.rigidbody);
    if(obd.collider != nullptr)
        collider=obd.collider->createCopy();
    if(obd.shape != nullptr)
        shape=new Shape(*obd.shape);
    for(unsigned int i=0; i < obd.behaviours.size(); i++)
        behaviours.push_back(obd.behaviours[i]->createCopy());
}

ObjectData& ObjectData::operator=(ObjectData const& obd) {
    transform=obd.transform;

    delete rigidbody;
    rigidbody= nullptr;

    delete collider;
    collider=nullptr;

    delete shape;
    shape=nullptr;

    while(!behaviours.empty())
    {
        delete behaviours[behaviours.size()-1];
        behaviours.pop_back();
    }

    if(obd.rigidbody != nullptr)
        rigidbody=new Rigidbody(*obd.rigidbody);
    if(obd.collider != nullptr)
        collider=obd.collider->createCopy();
    if(obd.shape != nullptr)
        shape=new Shape(*obd.shape);
    for(unsigned int i=0; i < obd.behaviours.size(); i++)
        behaviours.push_back(obd.behaviours[i]->createCopy());

    return *this;
}

ObjectData::~ObjectData() {
    delete rigidbody;
    delete collider;
    delete shape;
    while(!behaviours.empty())
    {
        delete behaviours[behaviours.size()-1];
        behaviours.pop_back();
    }
}

///checkers
bool ObjectData::hasRigidbody() { return rigidbody!=nullptr; }
bool ObjectData::hasCollider() { return collider!=nullptr; }
bool ObjectData::hasShape() { return shape!=nullptr; }


///setters
void ObjectData::setRigidbody(Rigidbody& rb) {
    delete rigidbody;
    rigidbody=new Rigidbody(rb);
}
void ObjectData::setRigidbody(Rigidbody&& rb) {
    delete rigidbody;
    rigidbody=new Rigidbody(rb);
}

void ObjectData::setCollider(Collider& col) {
    delete collider;
    collider=col.createCopy();
}
void ObjectData::setCollider(Collider&& col) {
    delete collider;
    collider=col.createCopy();
}

void ObjectData::setShape(Shape& sh) {
    delete shape;
    shape=new Shape(sh);
}
void ObjectData::setShape(Shape&& sh) {
    delete shape;
    shape=new Shape(sh);
}

void ObjectData::addBehaviour(Behaviour& behaviour) {
    behaviours.push_back(behaviour.createCopy());
}
void ObjectData::addBehaviour(Behaviour&& behaviour) {
    behaviours.push_back(behaviour.createCopy());
}

void ObjectData::setTransform(Transform const& t) { transform=t; }
void ObjectData::setPosition(Vector const& pos) { transform.setPosition(pos); }
void ObjectData::setRotation(double rotation_rad) { transform.setRotation(rotation_rad); }
void ObjectData::setRotationDeg(double rotation_deg) { transform.setRotationDeg(rotation_deg); }


///deleters
void ObjectData::deleteRigidbody() {
    delete rigidbody;
    rigidbody=nullptr;
}
void ObjectData::deleteCollider() {
    delete collider;
    collider=nullptr;
}
void ObjectData::deleteShape() {
    delete shape;
    shape=nullptr;
}