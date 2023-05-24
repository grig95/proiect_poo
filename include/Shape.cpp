#include "Shape.h"
#include "Vector.h"
#include "Transform.h"
#include "appexceptions.h"

///constructors, destructors, copy-assignment
Shape::Shape() : ObjectAttachment() {}

Shape::Shape(float radius, std::size_t point_count) : ObjectAttachment(), type(Type::Circle) {
    circle=new sf::CircleShape(radius, point_count);
    circle->setOrigin(radius, radius);
}

Shape::Shape(Vector const& size) : ObjectAttachment(), type(Type::Rectangle) {
    rectangle=new sf::RectangleShape(sf::Vector2f(size.getX(), size.getY()));
    rectangle->setOrigin(size.getX()/2, size.getY()/2);
}

Shape::Shape(Shape const& sh) : ObjectAttachment(), type(sh.type) {
    if(sh.circle!=nullptr)
        circle=new sf::CircleShape(*sh.circle);
    if(sh.rectangle!=nullptr)
        rectangle=new sf::RectangleShape(*sh.rectangle);
    if(sh.convex!=nullptr)
        convex=new sf::ConvexShape(*sh.convex);
}

Shape& Shape::operator=(Shape const& sh) {
    if(this==&sh)
        return *this;

    type=sh.type;

    if(sh.circle!=nullptr)
    {
        if(circle!=nullptr)
            *circle=*sh.circle;
        else
            circle=new sf::CircleShape(*sh.circle);
    }
    else if(circle!=nullptr)
    {
        delete circle;
        circle=nullptr;
    }

    if(sh.rectangle!=nullptr)
    {
        if(rectangle!=nullptr)
            *rectangle=*sh.rectangle;
        else
            rectangle=new sf::RectangleShape(*sh.rectangle);
    }
    else if(rectangle!=nullptr)
    {
        delete rectangle;
        rectangle=nullptr;
    }

    if(sh.convex!=nullptr)
    {
        if(convex!=nullptr)
            *convex=*sh.convex;
        else
            convex=new sf::ConvexShape(*sh.convex);
    }
    else if(convex!=nullptr)
    {
        delete convex;
        convex=nullptr;
    }

    return *this;
}

Shape::~Shape() {
    if(circle!=nullptr)
        delete circle;
    if(rectangle!=nullptr)
        delete rectangle;
    if(convex!=nullptr)
        delete convex;
}


///functionality
void Shape::render(sf::RenderWindow& window) const {
    if(transform==nullptr)
        throw missing_reference("Shape", "render()", "transform");

    switch (type) {
        case Type::Circle:
            circle->setPosition(transform->getPosition().getX(), -transform->getPosition().getY());
            window.draw(*circle);
            break;
        case Type::Rectangle:
            rectangle->setPosition(transform->getPosition().getX(), -transform->getPosition().getY());
            window.draw(*rectangle);
            break;
        case Type::Convex:
            convex->setPosition(transform->getPosition().getX(), -transform->getPosition().getY());
            window.draw(*convex);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
}


///'own' getter and setters
void Shape::setTransform(Transform *trans) { transform=trans; }

Shape& Shape::setType(Type t) {
    type=t;

    switch(type) {
        case Type::Circle:
            if(circle==nullptr)
            {
                circle = new sf::CircleShape();
                float radius = circle->getRadius();
                circle->setOrigin(radius, radius);
            }
            break;
        case Type::Rectangle:
            if(rectangle==nullptr)
            {
                rectangle=new sf::RectangleShape();
                sf::Vector2f size=rectangle->getSize();
                rectangle->setOrigin(size.x/2, size.y/2);
            }
            break;
        case Type::Convex:
            if(convex==nullptr)
                convex=new sf::ConvexShape();
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }

    return *this;
}

Shape::Type Shape::getType() const { return type; }


///common setters
Shape& Shape::setOrigin(Vector const& relCoord) {
    sf::FloatRect boundingBox;
    switch(type) {
        case Type::Circle:
            boundingBox=circle->getLocalBounds();
            circle->setOrigin(relCoord.getX(), boundingBox.height-relCoord.getY());
            break;
        case Type::Rectangle:
            boundingBox=rectangle->getLocalBounds();
            rectangle->setOrigin(relCoord.getX(), boundingBox.height-relCoord.getY());
            break;
        case Type::Convex:
            boundingBox=convex->getLocalBounds();
            convex->setOrigin(relCoord.getX(), boundingBox.height-relCoord.getY());
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}
Shape& Shape::setFillColor(sf::Color const& color) {
    switch(type) {
        case Type::Circle:
            circle->setFillColor(color);
            break;
        case Type::Rectangle:
            rectangle->setFillColor(color);
            break;
        case Type::Convex:
            convex->setFillColor(color);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}

Shape& Shape::setOutlineColor(sf::Color const& color) {
    switch(type) {
        case Type::Circle:
            circle->setOutlineColor(color);
            break;
        case Type::Rectangle:
            rectangle->setOutlineColor(color);
            break;
        case Type::Convex:
            convex->setOutlineColor(color);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}

Shape& Shape::setOutlineThickness(float thickness) {
    switch(type) {
        case Type::Circle:
            circle->setOutlineThickness(thickness);
            break;
        case Type::Rectangle:
            rectangle->setOutlineThickness(thickness);
            break;
        case Type::Convex:
            convex->setOutlineThickness(thickness);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}

Shape& Shape::setTexture(sf::Texture* texture) {
    switch(type) {
        case Type::Circle:
            circle->setTexture(texture);
            break;
        case Type::Rectangle:
            rectangle->setTexture(texture);
            break;
        case Type::Convex:
            convex->setTexture(texture);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}

Shape& Shape::setTextureRect(sf::IntRect const& texRect) {
    switch(type) {
        case Type::Circle:
            circle->setTextureRect(texRect);
            break;
        case Type::Rectangle:
            rectangle->setTextureRect(texRect);
            break;
        case Type::Convex:
            convex->setTextureRect(texRect);
            break;
        case Type::Undefined: ///small brain error made me do this
            break;
    }
    return *this;
}


///special setters
Shape& Shape::setRadius(float radius) {
    if(type!=Type::Circle)
        return *this;
    circle->setRadius(radius);
    return *this;
}
Shape& Shape::setPointCount(std::size_t count) {
    if(type==Type::Circle)
        circle->setPointCount(count);
    else if(type==Type::Convex)
        convex->setPointCount(count);
    return *this;
}
Shape& Shape::setPoint(std::size_t index, Vector const& point){
    if(type!=Type::Convex)
        return *this;
    convex->setPoint(index, sf::Vector2f(point.getX(), -point.getY()));

    sf::FloatRect boundingBox=convex->getLocalBounds();
    convex->setOrigin((boundingBox.left+boundingBox.width)/2, (boundingBox.top+boundingBox.height)/2);

    return *this;
}
Shape& Shape::setSize(Vector size) {
    if(type!=Type::Rectangle)
        return *this;
    rectangle->setSize(sf::Vector2f(size.getX(), size.getY()));
    rectangle->setOrigin(size.getX()/2, size.getY()/2);
    return *this;
}


///common getters
std::size_t Shape::getPointCount() const { /// "Error: Not all code paths return a value" ???????
    switch(type) {
        case Type::Circle:
            return circle->getPointCount();
        case Type::Rectangle:
            return rectangle->getPointCount();
        case Type::Convex:
            return convex->getPointCount();
        case Type::Undefined:
            throw app_exception("App exception in Shape object: getPointCount() method was called, but object is marked Undefined");
    }
    throw app_exception("App exception in Shape object: getPointCount() method was called and somehow jumped over the switch statement. Guess that annoying error was right somehow!");
}

Vector Shape::getPoint(std::size_t index) const {
    sf::Vector2f point; /// "Error: Not all code paths return a value" ???????
    switch(type) {
        case Type::Circle:
            point=circle->getPoint(index);
            return Vector(point.x, -point.y);
        case Type::Rectangle:
            point=rectangle->getPoint(index);
            return Vector(point.x, -point.y);
        case Type::Convex:
            point=convex->getPoint(index);
            return Vector(point.x, -point.y);
        case Type::Undefined:
            throw app_exception("App exception in Shape object: getPoint() method was called, but object is marked Undefined");
    }
    throw app_exception("App exception in Shape object: getPoint() method was called and somehow jumped over the switch statement. Guess that annoying error was right somehow!");
}

///special getters
float Shape::getRadius() const {
    if(type!=Type::Circle)
        throw app_exception("App exception in Shape object: getRadius() method was called, but object is not marked Circle.");
    return circle->getRadius();
}
Vector Shape::getSize() const {
    if(type!=Type::Rectangle)
        throw app_exception("App exception in Shape object: getSize() method was called, bot object is not marked Rectangle.");
    sf::Vector2f size=rectangle->getSize();
    return Vector(size.x, size.y);
}