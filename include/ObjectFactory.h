#ifndef OOP_OBJECTFACTORY_H
#define OOP_OBJECTFACTORY_H

class Object;
class ObjectData;

class ObjectFactory {
public:
    static Object* createSolidCircle(double radius=1);
    static Object* createShooter(ObjectData const& prefab, double speed, double cooldown);
};


#endif //OOP_OBJECTFACTORY_H
