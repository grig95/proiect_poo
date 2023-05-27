#include "ObjectFactory.h"
#include "ObjectDataFactory.h"
#include "Object.h"
#include "ObjectData.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Shape.h"

Object* ObjectFactory::createSolidCircle(double radius) {
    return new Object(ObjectDataFactory::getSolidCircleData(radius));
}

Object* ObjectFactory::createShooter(ObjectData const& prefab, double speed, double cooldown) {
    return new Object(ObjectDataFactory::getShooterData(prefab, speed, cooldown));
}