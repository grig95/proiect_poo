#include "Behaviour.h"

Behaviour::Behaviour() = default;
Behaviour::~Behaviour() = default;


void Behaviour::onRigidbodyDestroy() {}
void Behaviour::onColliderDestroy() {}
void Behaviour::onShapeDestroy() {}
void Behaviour::onBehaviourDestroy(Behaviour*) {}

void Behaviour::onRigidbodyChange(Rigidbody*) {}
void Behaviour::onColliderChange(Collider*) {}
void Behaviour::onShapeChange(Shape*) {}