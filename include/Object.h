#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H

#include "Transform.h"
#include "Behaviour.h"
#include "appexceptions.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Rigidbody;
class Collider;
class Shape;
class ObjectData;

class Object {
private:
    Transform transform;
    Rigidbody* rigidbody=nullptr;
    Collider* collider=nullptr;
    Shape* shape=nullptr;
    std::vector<Behaviour*> behaviours;

    void render(sf::RenderWindow& window) const;
    void update(double deltaTime);
public:
    Object();
    explicit Object(ObjectData const& obd);
    Object(Object const& obj); ///creates a new, identical object (with new, identical attachments)
    Object& operator=(Object const&); ///copies everything, including transform
    ~Object();

    void attachRigidbody(Rigidbody* rb);
    void attachCollider(Collider* col);
    void attachShape(Shape* sh);
    void attachBehaviour(Behaviour* behaviour);

    bool hasRigidbody();
    bool hasCollider();
    bool hasShape();
    template<typename T> bool hasBehaviour();

    void destroyRigidbody();
    void destroyCollider();
    void destroyShape();
    template<typename T> void destroyBehaviour();

    Transform& getTransform();
    Vector const& getPosition() const;
    double getRotation() const;
    Rigidbody& getRigidbody() const;
    Collider& getCollider() const;
    Shape& getShape() const;
    template<typename T> T& getBehaviour();

    friend class ObjectHandler;
    friend class ObjectData;
};



template<typename T> bool Object::hasBehaviour() {
    for(unsigned int i=0;i<behaviours.size();i++)
    {
        T* b = dynamic_cast<T*>(behaviours[i]);
        if(b!=nullptr)
            return true;
    }
    return false;
}

template<typename T> void Object::destroyBehaviour() {
    Behaviour* destroyed=nullptr;
    for(auto it=behaviours.begin();it!=behaviours.end();it++)
    {
        T* b=dynamic_cast<T*>(*it);
        if(b!=nullptr)
        {
            destroyed=*it;
            behaviours.erase(it);
            delete b;
            break;
        }
    }

    if(destroyed!=nullptr)
        for(unsigned int i=0;i<behaviours.size();i++)
            behaviours[i]->onBehaviourDestroy(destroyed);
}

template<typename T> T& Object::getBehaviour() {
    for(unsigned int i=0;i<behaviours.size();i++)
    {
        T* b = dynamic_cast<T*>(behaviours[i]);
        if(b!=nullptr)
            return *b;
    }
    throw missing_reference("Object", "getBehaviour<>()", "(unknown type)");
}


#endif //OOP_OBJECT_H
