#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Paddle.h"

using namespace std;
using namespace sf;


Paddle::Paddle(b2World& world) {
    if (paddleTex.loadFromFile("paddle.png")) {
        paddle.setTexture(paddleTex);
    }
    paddle.setScale(0.1f, 0.1f);
    b2BodyDef paddleDef;
    paddleDef.type = b2_dynamicBody;
    paddleDef.position.Set(400.0f, 550.0f);
    paddleBody = world.CreateBody(&paddleDef);
    paddleWidth = paddle.getGlobalBounds().width, paddleHeight = paddle.getGlobalBounds().height;
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(paddleWidth/2, paddleHeight/2);
    b2FixtureDef paddleFixtureDef;
    paddleFixtureDef.shape = &paddleShape;
    paddleFixtureDef.restitution = 0.0f;
    paddleFixtureDef.friction = 0.0f;
    paddleBody->CreateFixture(&paddleFixtureDef);
}

void Paddle::move(float x) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddleBody->GetPosition().x > paddleWidth / 2)
    {
        paddleBody->SetLinearVelocity(b2Vec2(-30.0f, 0.0f));


    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddleBody->GetPosition().x < x - paddleWidth / 2)
    {
        paddleBody->SetLinearVelocity(b2Vec2(30.0f, 0.0f));
    }
    else
    {
        paddleBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
}

b2Vec2 Paddle::getPos() {
    return paddleBody->GetPosition();
}
b2Body* Paddle::getBody() {
    return paddleBody;
}
void Paddle::draw(RenderWindow& window) {
    paddle.setPosition(paddleBody->GetPosition().x, paddleBody->GetPosition().y);
    
    window.draw(paddle);
}