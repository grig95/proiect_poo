#ifndef OOP_COLLISIONHANDLER_H
#define OOP_COLLISIONHANDLER_H

#include <set>

class Collider;
class CircleCollider;
class Collision;
class Vector;

class CollisionHandler {
private:
    std::set<Collider*> colliders;

    CollisionHandler();
    void track(Collider* collider);
    void untrack(Collider* collider);

    static void resolveCollision(Collision const& collision);
    static Vector getSurfaceToNormal(Vector const& normal);

    ///When writing collision detection functions, don't forget to treat and resolve the case in which neither collider has a rigidbody or they are both inactive.
    void CircleCircle(CircleCollider& col1, CircleCollider& col2, double deltaTime);
public:
    ~CollisionHandler();

    static CollisionHandler& getHandler();

    void checkCollisions(double deltaTime);

    CollisionHandler(CollisionHandler const&) = delete;
    CollisionHandler& operator=(CollisionHandler const&) = delete;

    friend class Collider;
};


#endif //OOP_COLLISIONHANDLER_H
