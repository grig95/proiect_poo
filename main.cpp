/// ----- PROBLEMS -----
/// 1. Rigidbody/Collider destructor deleting referenced Transform and causing errors when attempting to delete said Transform object again
/// 2. Nicer way to set ForceMode::Force as the default argument in Rigidbody.addForce()?

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "include/Rigidbody.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main() {
    #ifdef __linux__
    XInitThreads();
    #endif

    Vector v1(1.2, 3), v2, v3=v1;
    std::cout<<v1<<" "<<v2<<" "<<v3<<"\n";
    v3=v3+v1*2;
    v2=v3.normalized()*v3.magnitude();
    std::cout<<v1<<" "<<v2<<" "<<v3<<"\n";

    Transform t1(v1, Transform::degToRad(45)), t2=t1;
    std::cout<<t2<<" "<<t2.up()<<" "<<t2.right()<<'\n';
    t2.rotateDeg(483.5);
    std::cout<<t2<<" "<<t2.up()<<" "<<t2.right()<<'\n';
    t2.move(v2);
    t2.rotate(-9.5);
    std::cout<<t2<<" "<<t2.up()<<" "<<t2.right()<<'\n';

    std::cout<<'\n';
    Rigidbody rb1(t1, 1), rb2=rb1, rb3(t1, 1, 1, 0.2, 0.05);
    std::cout<<t1<<'\n';
    rb1.addForce(5*Vector::right());
    rb2.addForce((Vector::zero()));
    rb3.addForce(5*Vector::right());
    std::cout<<rb1.getAirDragCoefficient()<<' '<<rb2.getAirDragCoefficient()<<' '<<rb3.getAirDragCoefficient()<<'\n';
    std::cout<<rb1.getPosition()<<' '<<rb2.getPosition()<<' '<<rb3.getPosition()<<'\n';
    for(int i=1;i<=5;i++)
    {
        double deltaTime=1;
        rb1.step(deltaTime);
        rb2.step(deltaTime);
        rb3.step(deltaTime);
        std::cout<<rb1.getPosition()<<' '<<rb2.getPosition()<<' '<<rb3.getPosition()<<'\n';
    }


    /*
    sf::RenderWindow window;
    // NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:30
    window.create(sf::VideoMode({800, 700}), "My Window", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            switch(e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                break;
            default:
                break;
            }
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }
    */

    return 0;
}
