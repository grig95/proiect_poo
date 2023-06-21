#include "Behaviour.h"

Behaviour::Behaviour() = default;
Behaviour::~Behaviour() = default;


void Behaviour::onRigidbodyDestroy() {}
void Behaviour::onColliderDestroy() {}
void Behaviour::onShapeDestroy() {}
void Behaviour::onBehaviourDestroy(Behaviour*) {}

void Behaviour::onRigidbodyChange(Rigidbody* newRb) {}
void Behaviour::onColliderChange(Collider* newCollider) {}
void Behaviour::onShapeChange(Shape* newShape) {}