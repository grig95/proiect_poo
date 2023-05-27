#include "ObjectDataFactory.h"
#include "ObjectData.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Shape.h"
#include "Shooter.h"

ObjectData ObjectDataFactory::getSolidCircleData(double radius) {
    Rigidbody rb;
    CircleCollider collider(radius);
    Shape shape(radius);
    shape.setFillColor(sf::Color(10, 10, 170));

    ObjectData objData;
    objData.setRigidbody(rb);
    objData.setCollider(collider);
    objData.setShape(shape);

    return objData;
}

ObjectData ObjectDataFactory::getShooterData(ObjectData const& prefab, double speed, double cooldown) {
    ObjectData objData;
    objData.addBehaviour(Shooter(prefab, speed, cooldown));
    return objData;
}