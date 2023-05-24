#ifndef OOP_COLLIDER_H
#define OOP_COLLIDER_H

#include "ObjectAttachment.h"

#include <cstdint>

class Transform;
class Rigidbody;
class Vector;

class Collider : public ObjectAttachment {
public:
    enum class Type : uint8_t {
        Undefined,
        CircleCollider
    };
protected:
    Transform* transform;
    Rigidbody* rigidbody;
    Type type = Type::Undefined;
    bool isTrigger = false;

    void setTransform(Transform* t); ///meant to only be accessed by Object
    void setRigidbody(Rigidbody* rb); ///meant to only be accessed by Object
public:
    Collider(Type t);
    Collider(Collider const& col);
    Collider& operator=(Collider const& col);
    Collider() = delete;
    virtual ~Collider();

    virtual Collider* createCopy() const = 0;

    Vector const& getPosition() const;
    double getRotation() const;
    Transform& getTransform() const;
    Rigidbody& getRigidbody() const;
    Type getType() const;
    bool getIsTrigger() const;

    void setIsTrigger(bool tr);

    friend class Object; ///meant to only access setTransform() and setRigidbody()
};

#endif //OOP_COLLIDER_H
