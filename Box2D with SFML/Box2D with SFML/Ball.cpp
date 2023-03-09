#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Ball.h"

using namespace std;
using namespace sf;


Ball::Ball() {
    fireTimer = 0;
    if (ballTex.loadFromFile("star.png")) {
        ball.setTexture(ballTex);
    }
}
void Ball::fire(float x, float y, b2World& world, b2Vec2 force) {
    if (fireTimer < 20) {
        fireTimer++;
    }
    if (Mouse::isButtonPressed(Mouse::Left) && fireTimer >= 20) {
        b2BodyDef ballDef;
        ballDef.type = b2_dynamicBody;
        ballDef.position.Set(x, y - 50.f);
        b2Body* ballBody = world.CreateBody(&ballDef);
        b2CircleShape ballShape;
        ballShape.m_radius = 10.0f;
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.density = 0.000001f;
        ballFixtureDef.shape = &ballShape;
        ballFixtureDef.restitution = 1.0f;
        ballFixtureDef.friction = 0.0f;
        ballBody->CreateFixture(&ballFixtureDef);
        ballBody->SetLinearVelocity(force);
        balls.push_back(ballBody);
        fireTimer = 0;
    }
}
vector<b2Body*> Ball::getBalls() {
    return balls;
}
void Ball::setBalls(vector<b2Body*>& tempBalls) {
    balls = tempBalls;
}
void Ball::draw(RenderWindow& window) {
    for (int i = 0; i < balls.size(); i++) {
        ball.setScale(0.09f, 0.09f);
        Vector2f ballPosition(balls[i]->GetPosition().x, balls[i]->GetPosition().y);
        ball.setPosition(ballPosition);
        window.draw(ball);
    }
}
