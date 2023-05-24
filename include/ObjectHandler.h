#ifndef OOP_OBJECTHANDLER_H
#define OOP_OBJECTHANDLER_H

#include <set>

#include <SFML/Graphics.hpp>

class Object;

class ObjectHandler {
private:
    std::set<Object*> objects;

    ObjectHandler();
    void track(Object* obj);
    void untrack(Object* obj);
public:
    static ObjectHandler& getHandler();

    ~ObjectHandler();

    void render(sf::RenderWindow& window) const;
    void update(double deltaTime) const;

    ObjectHandler(ObjectHandler const&) = delete;
    ObjectHandler& operator=(ObjectHandler const&) = delete;


    friend class Object;
};


#endif //OOP_OBJECTHANDLER_H
