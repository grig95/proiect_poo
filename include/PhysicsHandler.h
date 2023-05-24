#ifndef OOP_PHYSICSHANDLER_H
#define OOP_PHYSICSHANDLER_H

#include <set>

class Rigidbody;
class Collision;

class PhysicsHandler {
private:
    std::set<Rigidbody*> rbodies;

    PhysicsHandler();
    void track(Rigidbody* rb);
    void untrack(Rigidbody* rb);

    static void resolveCollision(Collision const& collision);
public:
    ~PhysicsHandler();
    static PhysicsHandler& getHandler();

    void step(double deltaTime);

    PhysicsHandler(PhysicsHandler const&) = delete;
    PhysicsHandler& operator=(PhysicsHandler const&) = delete;

    friend class Rigidbody;
    friend class CollisionHandler; ///meant to only access resolveCollision()
};


#endif //OOP_PHYSICSHANDLER_H
