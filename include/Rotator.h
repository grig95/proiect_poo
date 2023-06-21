#ifndef OOP_ROTATOR_H
#define OOP_ROTATOR_H

#include "Behaviour.h"

class Transform;

class Rotator : public Behaviour {
protected:
    double rotationSpeed;
    Transform* transform=nullptr;

    void start() override;
    void update(double deltaTime) override;
public:
    explicit Rotator(double rotationSpeed);
    Rotator(Rotator const& rotator);
    Rotator& operator=(Rotator const&);
    ~Rotator();

    Rotator()=delete;

    Behaviour* createCopy() override;
};


#endif //OOP_ROTATOR_H
