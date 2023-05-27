#ifndef OOP_OBJECTDATAFACTORY_H
#define OOP_OBJECTDATAFACTORY_H

class ObjectData;

class ObjectDataFactory {
public:
    static ObjectData getSolidCircleData(double radius=1);
    static ObjectData getShooterData(ObjectData const& prefab, double speed, double cooldown);
};


#endif //OOP_OBJECTDATAFACTORY_H
