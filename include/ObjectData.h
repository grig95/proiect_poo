#ifndef OOP_OBJECTDATA_H
#define OOP_OBJECTDATA_H

#include "Transform.h"

#include <vector>

class Rigidbody;
class Collider;
class Shape;
class Behaviour;
class Object;

class ObjectData {
private:
    Transform transform;
    Rigidbody* rigidbody=nullptr;
    Collider* collider=nullptr;
    Shape* shape=nullptr;
    std::vector<Behaviour*> behaviours;
public:
    ObjectData();
    explicit ObjectData(Object const& obj);
    ObjectData(ObjectData const& obd);
    ObjectData& operator=(ObjectData const& obd);
    ~ObjectData();

    bool hasRigidbody();
    bool hasCollider();
    bool hasShape();
    template<typename T> bool hasBehaviour() {
        for(unsigned int i=0;i<behaviours.size();i++)
        {
            T* b = dynamic_cast<T*>(behaviours[i]);
            if(b!=nullptr)
                return true;
        }
        return false;
    }

    ///these will copy the parameter to a new location in memory and keep that
    void setRigidbody(Rigidbody const& rb);
    void setRigidbody(Rigidbody&& rb);
    void setCollider(Collider const& col);
    void setCollider(Collider&& col);
    void setShape(Shape const& sh);
    void setShape(Shape&& sh);
    void addBehaviour(Behaviour& behaviour);
    void addBehaviour(Behaviour&& behaviour);

    void setTransform(Transform const& t);
    void setPosition(Vector const& pos);
    void setRotation(double rotation_rad);
    void setRotationDeg(double rotation_deg);

    void deleteRigidbody();
    void deleteCollider();
    void deleteShape();
    template<typename T> void deleteBehaviour() {
        for(auto it=behaviours.begin();it!=behaviours.end();it++)
        {
            T* b=dynamic_cast<T*>(*it);
            if(b!=nullptr)
            {
                behaviours.erase(it);
                delete b;
                break;
            }
        }
    }

    friend class Object;
};


#endif //OOP_OBJECTDATA_H
