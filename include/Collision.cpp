#include "Collision.h"

Collision::Collision(Collision const& collision) = default;

Collision::Collision(double timeElapsed, const Vector &contactPoint, Collider &col1, Collider &col2,
                     const Transform &t1, const Transform &t2, const Vector &normal1, const Vector &normal2) :
        timeElapsed(timeElapsed), contactPoint(contactPoint), collider1(col1), collider2(col2), transform1(t1), transform2(t2), normal1(normal1), normal2(normal2) {}

Collision::~Collision() = default;

double Collision::getTimeElapsed() const { return timeElapsed; }
Vector const& Collision::getContactPoint() const { return contactPoint; }
Collider& Collision::getCollider1() const { return collider1; }
Collider& Collision::getCollider2() const { return collider2; }
Transform const& Collision::getTransform1() const { return transform1; }
Transform const& Collision::getTransform2() const { return transform2; }
Vector const& Collision::getNormal1() const { return normal1; }
Vector const& Collision::getNormal2() const { return normal2; }