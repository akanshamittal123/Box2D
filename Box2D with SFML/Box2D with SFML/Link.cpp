#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Link.h"


Link::Link(b2World& world, b2Body* prevBody, float x, float y, float radius, float density, float friction) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    body = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;

    if (prevBody != nullptr) {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(prevBody, body, prevBody->GetWorldCenter(), body->GetWorldCenter());
        jointDef.length = 100.f;
        jointDef.stiffness = 0.0f;
        jointDef.collideConnected = true;
        jointDef.damping = 0.5f;
        world.CreateJoint(&jointDef);
    }

    body->CreateFixture(&fixtureDef);
}

void Link::draw(sf::RenderWindow& window) const {
    b2Vec2 pos = body->GetPosition();
    sf::CircleShape link(radius);
    link.setFillColor(sf::Color::Color(205, 133, 63));
    link.setOrigin(radius, radius);
    link.setPosition(pos.x, pos.y);
    window.draw(link);
}

b2Body* Link::getBody() const { return body; }

