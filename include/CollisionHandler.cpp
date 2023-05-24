#include "CollisionHandler.h"
#include "appexceptions.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "Vector.h"
#include "PhysicsHandler.h"


CollisionHandler::CollisionHandler() = default;
CollisionHandler::~CollisionHandler() = default;

CollisionHandler& CollisionHandler::getHandler() {
    static CollisionHandler handler;
    return handler;
}

void CollisionHandler::track(Collider* collider) {
    if(collider==nullptr)
        return;
    colliders.insert(collider);
}

void CollisionHandler::untrack(Collider *collider) {
    colliders.erase(collider);
}


///collision logic
void CollisionHandler::checkCollisions(double deltaTime) {
    for(auto it1=colliders.begin();it1!=colliders.end();it1++) {
        if(!(*it1)->isAttached())
            continue;

        auto it2=it1;
        it2++;
        for(;it2!=colliders.end();it2++)
        {
            if(!(*it2)->isAttached())
                continue;
            if((*it1)->getIsTrigger()&&(*it2)->getIsTrigger())
                continue;

            if((*it1)->getType()==Collider::Type::CircleCollider)
            {
                if((*it2)->getType()==Collider::Type::CircleCollider)
                    CircleCircle(dynamic_cast<CircleCollider&>(**it1), dynamic_cast<CircleCollider&>(**it2), deltaTime);
            }
        }
    }
}

void CollisionHandler::CircleCircle(CircleCollider& col1, CircleCollider& col2, double deltaTime) {
    double distance=(col1.getPosition()-col2.getPosition()).magnitude();
    if(distance<=col1.getRadius()+col2.getRadius())
    {
        ///collision detected

        if(col1.getIsTrigger()||col2.getIsTrigger())
        {
            /// !!!! FIRE COLLISION EVENT FOR THE TRIGGER COLLIDER !!!!
            return;
        }

        ///calculate original contact point and time elapsed since first contact
        ///then create a Collision object and pass it
        Vector vel1, vel2;
        int c=0;
        try { vel1=col1.getRigidbody().getVelocity(); }
        catch(missing_reference& mr) { vel1=Vector::zero(); c++; }
        try { vel2=col2.getRigidbody().getVelocity(); }
        catch(missing_reference& mr) { vel2=Vector::zero(); c++; }

        if(c==2)
        {
            ///neither collider has a rigidbody
            ///simply move them away from each other so that they only touch and return
            Vector direction=(col1.getPosition()-col2.getPosition()).normalized();
            double distanceToMove=col1.getRadius()+col2.getRadius()-(col1.getPosition()-col2.getPosition()).magnitude();
            col1.getTransform().move(direction*distanceToMove);
            col2.getTransform().move(-direction*distanceToMove);
            return;
        }


        Vector relVel=vel1-vel2, relPos=col1.getPosition()-col2.getPosition();
        double delta=4*( (relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) * (relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) ) -
                4*( relVel.getX()*relVel.getX() + relVel.getY()*relVel.getY() )*( relPos.getX()*relPos.getX() + relPos.getY()*relPos.getY() -
                        (col1.getRadius()+col2.getRadius())*(col1.getRadius()+col2.getRadius()) );
        if(delta<0)
            throw math_error(std::string("Math error: Variable delta should not be negative. (CollisionHandler.CircleCircle) (delta=")+std::to_string(delta)+std::string(")"));

        double timeSinceFirstContact, t1, t2;
        t1=( 2*(relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) - sqrt(delta) ) / (2*( relVel.getX()*relVel.getX() + relVel.getY()*relVel.getY() ));
        t2=( 2*(relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) + sqrt(delta) ) / (2*( relVel.getX()*relVel.getX() + relVel.getY()*relVel.getY() ));

        t1=std::max(t1, 0.0);
        t2=std::max(t2, 0.0);
        timeSinceFirstContact=std::min(std::min(t1, t2), deltaTime);

        Transform transform1=col1.getTransform(), transform2=col2.getTransform();
        transform1.move(-vel1*timeSinceFirstContact);
        transform2.move(-vel2*timeSinceFirstContact);

        double rotVel;
        try { rotVel=col1.getRigidbody().getAngularVelocity(); }
        catch(missing_reference& mr) { rotVel=0; }
        transform1.rotate(-rotVel*timeSinceFirstContact);
        try { rotVel=col2.getRigidbody().getAngularVelocity(); }
        catch(missing_reference& mr) { rotVel=0; }
        transform2.rotate(-rotVel*timeSinceFirstContact);

        Vector contactPoint = transform1.getPosition() + (transform2.getPosition()-transform1.getPosition()).normalized() *
                (col1.getRadius() + ((transform2.getPosition()-transform1.getPosition()).magnitude() - col1.getRadius() - col2.getRadius())/2 );

        Vector normal1=(transform2.getPosition()-transform1.getPosition()).normalized();
        Vector normal2=(transform1.getPosition()-transform2.getPosition()).normalized();

        Collision collision(timeSinceFirstContact, contactPoint, col1, col2, transform1, transform2, normal1, normal2);
        PhysicsHandler::resolveCollision(collision);

    }
}