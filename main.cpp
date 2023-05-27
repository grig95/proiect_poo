/// ---- QUESTIONS ----
/// 1. Behaviour has 4 virtual methods that are are called when various attachments of the Object it is attached to are deleted, so it knows when
/// potential references to these attachments are invalidated. Should these be purely virtual to make sure the programmer doesn't accidentally forget
/// to treat such cases or should they just do nothing by default to not be overly annoying?

/// ---- TO DO ----
/// 1. Give Shape a depth/order/z-coordinate member and move the rendering functionality from ObjectHandler to allow shapes to be correctly drawn over
/// each other.
/// 2. Have Object keep track of its last Transform and use that to determine speed and rotational speed when it collides with rigidbody objects.
/// 3. Implement collision events.

/// ---- REMEMBER ----
/// 1. Specialize Rigidbody's addForceToRelativePoint() function.
/// 2. Check the physics behind the momentum distribution in a collision.
/// 3. In Object, the Behaviour.start() method is called for initialization everytime a new Behaviour is attached. This can create problems if behaviours
/// that depend on each other are not attached in the proper order or in cases of circular dependencies. One possible fix is implementing a BehaviourStart
/// event at the beginning of each frame and having all behaviours' start methods (that aren't initialized yet) be called then.

/// ---- OPTIMIZATIONS ----
/// 1. CollisionHandler checks for collisions between every pair of colliders. Implement a data structure that will allow it to check only for collisions
/// between colliders that are close by.
/// 2. Handlers that require the handled object to be attached to an Object can be sped up by having them store attached and unattached objects in different
/// locations and swapping them around when attachTo() and detach() are called. (may also want to make attachTo() take a reference as the argument)

/// ---- SUGGESTIONS (low priority) ----
/// 1. It may be better to have ObjectAttachment.attachTo() be a virtual function that will both fulfill its current role and be responsible for
/// getting all the other necessary attachments from the Object (and the transform, basically all dependencies). This will mess up the BehaviourStart
/// initialization event described above, so just have Behaviour override attachTo() as a non-virtual function that does its current job and keep the
/// rest of the dependency gathering in start().
/// 2. It may be a good idea to have CollisionHandler rely on a less accurate but more robust method of retrieving a collision point and time when
/// rolling back the simulation fails for whatever reason (floating point inaccuracy?) and an exception is normally thrown.


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "include/Vector.h"
#include "include/Transform.h"
#include "include/Rigidbody.h"
#include "include/CircleCollider.h"
#include "include/PhysicsHandler.h"
#include "include/CollisionHandler.h"
#include "include/Object.h"
#include "include/ObjectHandler.h"
#include "include/ObjectFactory.h"
#include "include/ObjectDataFactory.h"
#include "include/Shape.h"
#include "include/Shooter.h"

#include "include/appexceptions.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main() {
    #ifdef __linux__
    XInitThreads();
    #endif

    sf::RenderWindow window;
    // NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:30
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    float unitToPixelSize=100;
    sf::View view(sf::Vector2f(0.0, 0.0), sf::Vector2f(window.getSize().x/unitToPixelSize, window.getSize().y/unitToPixelSize));
    window.setView(view);


    ObjectData circle1 = ObjectDataFactory::getSolidCircleData(0.5);

    ObjectData circle2;
    circle2.setCollider(CircleCollider(0.25));
    circle2.setShape(Shape(0.25).setFillColor(sf::Color::Magenta));
    circle2.setRigidbody(Rigidbody(0.5));

    Object* shooter1=ObjectFactory::createShooter(circle1, 4, 1);
    Object* shooter2=ObjectFactory::createShooter(circle2, 8, 1);

    shooter1->getTransform()=Transform(Vector(-3, 0.25), Transform::degToRad(-90));
    shooter2->getTransform()=Transform(Vector(3, -0.25), Transform::degToRad(90));


    sf::Clock clock;
    while(window.isOpen()) {
        sf::Time deltaTime=clock.restart();

        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                view.setSize(window.getSize().x/unitToPixelSize, window.getSize().y/unitToPixelSize);
                window.setView(view);
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                break;
            default:
                break;
            }
        }

        ObjectHandler::getHandler().update(deltaTime.asSeconds());

        PhysicsHandler::getHandler().step(deltaTime.asSeconds());

        CollisionHandler::getHandler().checkCollisions(deltaTime.asSeconds());

        window.clear();

        ObjectHandler::getHandler().render(window);

        window.display();
    }


    return 0;
}
