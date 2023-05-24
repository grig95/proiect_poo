#ifndef OOP_OBJECTFACTORY_H
#define OOP_OBJECTFACTORY_H

class Object;

class ObjectFactory {
public:
    static Object* getSolidCircle(double radius=1);
};


#endif //OOP_OBJECTFACTORY_H
