/// ---- TO DO ----
/// 1. Give Shape a depth/order/z-coordinate member and move the rendering functionality from ObjectHandler to allow shapes to be correctly drawn over
/// each other.
/// 2. Implement collision events.

/// ---- OPTIMIZATIONS ----
/// 1. CollisionHandler checks for collisions between every pair of colliders. Implement a data structure that will allow it to check only for collisions
/// between colliders that are close by.
/// 2. Handlers that require the handled object to be attached to an Object can be sped up by having them store attached and unattached objects in different
/// locations and swapping them around when attachTo() and detach() are called. (may also want to make attachTo() take a reference as the argument)

/// ---- SUGGESTIONS (low priority) ----
/// 1. It may be a good idea to have CollisionHandler rely on a less accurate but more robust method of retrieving a collision point and time when
/// rolling back the simulation fails for whatever reason (floating point inaccuracy?) and an exception is normally thrown.


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "include/Transform.h"
#include "include/Rigidbody.h"

#include "include/Vector.h"
#include "include/Transform.h"
#include "include/Rigidbody.h"
#include "include/CircleCollider.h"
#include "include/PhysicsHandler.h"
#include "include/CollisionHandler.h"
#include "include/Object.h"
#include "include/ObjectHandler.h"
#include "include/RigidbodyBuilder.h"
#include "include/ObjectFactory.h"

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


    /*sf::CircleShape center(0.2);
    center.setFillColor(sf::Color(0, 255, 0));
    center.setPosition(0.0, 0.0);
    center.setOrigin(0.2, 0.2);

    sf::CircleShape circle(1.0);
    circle.setFillColor(sf::Color(255, 0, 0));
    circle.setPosition(0.0, 0.0);
    circle.setOrigin(1, 1);*/

    Object* circle = ObjectFactory::getSolidCircle(0.5);
    circle->getTransform().setPosition(Vector(-3, 0));

    Object* circle2 = ObjectFactory::getSolidCircle(0.25);
    circle2->getTransform().setPosition({3, 0});
    circle2->getRigidbody().addForce({-2, 0}, Rigidbody::ForceMode::Impulse);

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
        //using namespace std::chrono_literals;
        //std::this_thread::sleep_for(300ms);

        circle->getRigidbody().addForce(Vector(2, 0));

        PhysicsHandler::getHandler().step(deltaTime.asSeconds());

        CollisionHandler::getHandler().checkCollisions(deltaTime.asSeconds());

        window.clear();

        ObjectHandler::getHandler().render(window);

        window.display();
    }


    return 0;
}
