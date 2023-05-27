#include "CollisionHandler.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Collision.h"
#include "Vector.h"

#include "appexceptions.h"

#include <iostream>
#include <cmath>

///just debugging
#include "Object.h"
#include "Shape.h"

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
void CollisionHandler::resolveCollision(const Collision &collision) {
    Vector surface1 = getSurfaceToNormal(collision.getNormal1());
    Vector surface2 = getSurfaceToNormal(collision.getNormal2());

    Rigidbody* rb1;
    Rigidbody* rb2;

    try { rb1=&collision.getCollider1().getRigidbody(); }
    catch(missing_reference&) { rb1=nullptr; }
    try { rb2=&collision.getCollider2().getRigidbody(); }
    catch(missing_reference&) { rb2=nullptr; }

    if(rb1==nullptr||!rb1->getActivation())
    {
        if(rb2==nullptr||!rb2->getActivation())
            throw app_exception("Incorrect responsibility handling: CollisionHandler::resolveCollision(Collision const&) is never supposed to be called when both "
                                "rigidbodies are effectively disabled (they either don't exist or are inactive). The handling of the rigidbodyless case is the "
                                "collision detection functions' responsibility");

        ///rb1 is inactive or doesn't exist, put all the energy into rb2
        Vector impactMomentum2 = -2 * rb2->getBounciness() * rb2->getVelocity() * rb2->getMass();

        double delta=surface2.getX()*collision.getNormal2().getY() - surface2.getY()*collision.getNormal2().getX();
        double deltaX= impactMomentum2.getX() * collision.getNormal2().getY() - impactMomentum2.getY() * collision.getNormal2().getX();
        double deltaY= surface2.getX() * impactMomentum2.getY() - surface2.getY() * impactMomentum2.getX();

        double x2=deltaX/delta;
        double y2=deltaY/delta;

        double frictionForce2=rb2->getFrictionCoefficient()*std::abs(y2);

        rb2->addForceAtRelativePoint(std::max(x2 - frictionForce2, 0.0) * surface2, collision.getContactPoint() - collision.getTransform2().getPosition(), Rigidbody::ForceMode::Impulse);
        rb2->addForceAtRelativePoint(y2*collision.getNormal2(), collision.getContactPoint() - collision.getTransform2().getPosition(), Rigidbody::ForceMode::Impulse);

        return;
    }
    else if(rb2==nullptr||!rb2->getActivation())
    {
        if(rb1==nullptr||!rb1->getActivation())
            throw app_exception("Incorrect responsibility handling: CollisionHandler::resolveCollision(Collision const&) is never supposed to be called when both "
                                "rigidbodies are effectively disabled (they either don't exist or are inactive). The handling of the rigidbodyless case is the "
                                "collision detection functions' responsibility");

        ///rb2 is inactive or doesn't exist, put all the energy into rb1
        Vector impactMomentum1 = -2 * rb1->getBounciness() * rb1->getVelocity() * rb1->getMass();

        double delta=surface1.getX()*collision.getNormal1().getY() - surface1.getY()*collision.getNormal1().getX();
        double deltaX= impactMomentum1.getX() * collision.getNormal1().getY() - impactMomentum1.getY() * collision.getNormal1().getX();
        double deltaY= surface1.getX() * impactMomentum1.getY() - surface1.getY() * impactMomentum1.getX();

        double x1=deltaX/delta;
        double y1=deltaY/delta;

        double frictionForce1=rb1->getFrictionCoefficient()*std::abs(y1);

        rb1->addForceAtRelativePoint(std::max(x1 - frictionForce1, 0.0) * surface1, collision.getContactPoint() - collision.getTransform1().getPosition(), Rigidbody::ForceMode::Impulse);
        rb1->addForceAtRelativePoint(y1*collision.getNormal1(), collision.getContactPoint() - collision.getTransform1().getPosition(), Rigidbody::ForceMode::Impulse);

        return;
    }

    ///both rigidbodies exist and are active
    Vector relativeDirection1=(rb2->getVelocity()-rb1->getVelocity()).normalized();
    Vector relativeDirection2=-relativeDirection1;

    double totalPreservedMomentum = (2*rb2->getVelocity()*rb2->getMass() - 2*rb1->getVelocity()*rb1->getMass()).magnitude()
                                    * Rigidbody::bouncinessCombinationFunction(rb1->getBounciness(), rb2->getBounciness());
    double momentumFraction1=rb1->getBounciness()/std::max(rb1->getBounciness()+rb2->getBounciness(), 0.0);
    double momentumFraction2=1-momentumFraction1;

    Vector momentum1=momentumFraction1*totalPreservedMomentum*relativeDirection1;
    Vector momentum2=momentumFraction2*totalPreservedMomentum*relativeDirection2;

    double frictionCoefficient=Rigidbody::frictionCoefficientCombinationFunction(rb1->getFrictionCoefficient(), rb2->getFrictionCoefficient());

    ///solve and add forces to rb1
    double delta1=surface1.getX()*collision.getNormal1().getY() - surface1.getY()*collision.getNormal1().getX();
    double delta1X= momentum1.getX() * collision.getNormal1().getY() - momentum1.getY() * collision.getNormal1().getX();
    double delta1Y= surface1.getX() * momentum1.getY() - surface1.getY() * momentum1.getX();

    double x1=delta1X/delta1;
    double y1=delta1Y/delta1;

    double frictionForce1=frictionCoefficient*std::abs(y1);

    rb1->addForceAtRelativePoint(std::max(x1 - frictionForce1, 0.0) * surface1, collision.getContactPoint() - collision.getTransform1().getPosition(), Rigidbody::ForceMode::Impulse);
    rb1->addForceAtRelativePoint(y1*collision.getNormal1(), collision.getContactPoint() - collision.getTransform1().getPosition(), Rigidbody::ForceMode::Impulse);


    ///solve and add forces to rb2
    double delta2=surface2.getX()*collision.getNormal2().getY() - surface2.getY()*collision.getNormal2().getX();
    double delta2X= momentum2.getX() * collision.getNormal2().getY() - momentum2.getY() * collision.getNormal2().getX();
    double delta2Y= surface2.getX() * momentum2.getY() - surface2.getY() * momentum2.getX();

    double x2=delta2X/delta2;
    double y2=delta2Y/delta2;

    double frictionForce2=frictionCoefficient*std::abs(y2);

    rb2->addForceAtRelativePoint(std::max(x2 - frictionForce2, 0.0) * surface2, collision.getContactPoint() - collision.getTransform2().getPosition(), Rigidbody::ForceMode::Impulse);
    rb2->addForceAtRelativePoint(y2*collision.getNormal2(), collision.getContactPoint() - collision.getTransform2().getPosition(), Rigidbody::ForceMode::Impulse);
}

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
        try { vel1=col1.getRigidbody().getVelocity(); if(!col1.getRigidbody().getActivation()) c++; }
        catch(missing_reference&) { vel1=Vector::zero(); c++; }
        try { vel2=col2.getRigidbody().getVelocity(); if(!col2.getRigidbody().getActivation()) c++; }
        catch(missing_reference&) { vel2=Vector::zero(); c++; }

        if(c==2)
        {
            ///neither collider has a rigidbody or both are inactive
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
        t1=( 2*(relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) - sqrt(delta) ) / (2 * relVel.magnitude());
        t2=( 2*(relPos.getX()*relVel.getX() + relPos.getY()*relVel.getY()) + sqrt(delta) ) / (2* relVel.magnitude());

        if(std::isnan(t1)||std::isnan(t2)) /// in weird cases, the relative velocity can be 0
            t1=t2=0;

        t1=std::max(t1, 0.0);
        t2=std::max(t2, 0.0);
        timeSinceFirstContact=std::min(std::min(t1, t2), deltaTime);

        Transform transform1=col1.getTransform(), transform2=col2.getTransform();
        transform1.move(-vel1*timeSinceFirstContact);
        transform2.move(-vel2*timeSinceFirstContact);

        double rotVel;
        try { rotVel=col1.getRigidbody().getAngularVelocity(); }
        catch(missing_reference&) { rotVel=0; }
        transform1.rotate(-rotVel*timeSinceFirstContact);
        try { rotVel=col2.getRigidbody().getAngularVelocity(); }
        catch(missing_reference&) { rotVel=0; }
        transform2.rotate(-rotVel*timeSinceFirstContact);

        Vector contactPoint = transform1.getPosition() + (transform2.getPosition()-transform1.getPosition()).normalized() *
                (col1.getRadius() + ((transform2.getPosition()-transform1.getPosition()).magnitude() - col1.getRadius() - col2.getRadius())/2 );

        Vector normal1=(transform2.getPosition()-transform1.getPosition()).normalized();
        Vector normal2=(transform1.getPosition()-transform2.getPosition()).normalized();

        Collision collision(timeSinceFirstContact, contactPoint, col1, col2, transform1, transform2, normal1, normal2);
        resolveCollision(collision);
    }
}

Vector CollisionHandler::getSurfaceToNormal(const Vector &normal) {
    Vector surface;
    if(normal.getY()>0) ///surface.x will be > 0
    {
        surface.setX( std::abs(normal.getY()) );
        if(normal.getX()>0)
            surface.setY( -std::abs(normal.getX()) );
        else
            surface.setY( std::abs(normal.getX()) );
    }
    else
    {
        surface.setX( -std::abs(normal.getY()) );
        if(normal.getX()>0)
            surface.setY( -std::abs(normal.getX()) );
        else
            surface.setY( std::abs(normal.getX()) );
    }

    return surface;
}