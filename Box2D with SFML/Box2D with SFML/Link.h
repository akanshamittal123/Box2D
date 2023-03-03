#ifndef LINK_H
#define LINK_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Link {
public:
    Link(b2World& world, b2Body* prevBody, float x, float y, float radius, float density, float friction);

    void draw(sf::RenderWindow& window) const;

    b2Body* getBody() const;

private:
    b2Body* body;
    float radius = 10.0f;
};

#endif
