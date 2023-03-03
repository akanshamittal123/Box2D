#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Ground.h"

Ground::Ground(b2World& world, float x, float y, float width, float height) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(x, y);
    body = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(width, height);

    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 5.0f;
    groundFixtureDef.friction = 10.0f;
    body->CreateFixture(&groundFixtureDef);
}

void Ground::draw(sf::RenderWindow& window) const {
    sf::RectangleShape ground(sf::Vector2f(width * 2.0f, height * 2.0f));
    ground.setFillColor(sf::Color::Color(101, 67, 33));
    ground.setOrigin(width, height);
    ground.setPosition(body->GetPosition().x, body->GetPosition().y);
    window.draw(ground);
}