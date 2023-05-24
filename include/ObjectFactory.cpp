#include "ObjectFactory.h"
#include "Object.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Shape.h"

Object* ObjectFactory::getSolidCircle(double radius) {
    Rigidbody* rb=new Rigidbody();
    CircleCollider* collider=new CircleCollider(radius);
    Shape* shape=new Shape(radius);
    shape->setFillColor(sf::Color(10, 10, 170));

    Object* obj=new Object();
    obj->attachRigidbody(*rb);
    obj->attachCollider(*collider);
    obj->attachShape(*shape);

    return obj;
}