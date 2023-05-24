#ifndef OOP_SHAPE_H
#define OOP_SHAPE_H

#include "ObjectAttachment.h"

#include <SFML/Graphics.hpp>

class Vector;
class Transform;

class Shape : public ObjectAttachment {
public:
    enum class Type : uint8_t {
        Undefined,
        Circle,
        Rectangle,
        Convex
    };
private:
    Transform* transform=nullptr;
    sf::CircleShape* circle=nullptr;
    sf::RectangleShape* rectangle=nullptr;
    sf::ConvexShape* convex=nullptr;
    Type type=Type::Undefined;

    void render(sf::RenderWindow& window) const; ///meant to only be accessed by Object or whatever ends up passing rendering responsibility to this

    void setTransform(Transform* trans); ///meant to only be accessed by Object
public:
    Shape();
    explicit Shape(float radius, std::size_t point_count=30); /// creates  a circle
    explicit Shape(Vector const& size); /// creates a rectangle
    Shape(Shape const& sh);
    Shape& operator=(Shape const& sh);
    ~Shape();

    Shape& setType(Type t);
    Type getType() const;

    ///these setters will only modify the current type
    Shape& setOrigin(Vector const& relCoords); ///coordonates relative to bottom-left corner of the bounding box (in worlds coords, not sfml coords)
    Shape& setFillColor(sf::Color const& color);
    Shape& setOutlineColor(sf::Color const& color);
    Shape& setOutlineThickness(float thickness);
    Shape& setTexture(sf::Texture* texture);
    Shape& setTextureRect(sf::IntRect const& texRect);

    ///these setters will not to anything if they do not match the current type and will act only upon the current type
    Shape& setRadius(float radius); ///Circle
    Shape& setPointCount(std::size_t count); ///Circle or Convex
    Shape& setPoint(std::size_t index, Vector const& point); ///Convex
    Shape& setSize(Vector size); ///Rectangle

    ///common getters, these will throw an error only if the object is marked Undefined
    std::size_t getPointCount() const;
    Vector getPoint(std::size_t index) const;

    ///special getters, these will throw an error if the current type is not the required type
    float getRadius() const;
    Vector getSize() const;

    friend class Object; /// meant to only access setTransform()
};


#endif //OOP_SHAPE_H
