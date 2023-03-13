#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Ball.h"

using namespace std;
using namespace sf;

//Balls to shoot the bricks

//Constructor
Ball::Ball() {
    fireTimer = 0;
    if (ballTex.loadFromFile("star.png")) {
        ball.setTexture(ballTex);
    }
}

//mechanism to fire a ball
void Ball::fire(float x, float y, b2World& world , RenderWindow&window, float &veloMag) {
     // it is used to handle number of fires per click 
    if (fireTimer < 15) {
        fireTimer++;
    }
    
    if (Mouse::isButtonPressed(Mouse::Left) && fireTimer >= 15) {
        b2Vec2 mousePos(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
        b2Vec2 paddlePos(x, y);
        b2Vec2 resultantVect = mousePos - paddlePos;
        b2BodyDef ballDef;
        ballDef.type = b2_dynamicBody;
        ballDef.position.Set(x, y - 50.f);
        b2Body* ballBody = world.CreateBody(&ballDef);
        b2CircleShape ballShape;
        ballShape.m_radius = 1.0f;
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.density = 1.f;
        ballFixtureDef.shape = &ballShape;
        ballFixtureDef.restitution = 1.0f;
        ballFixtureDef.friction = 0.0f;
        ballBody->CreateFixture(&ballFixtureDef);
        resultantVect.Normalize();
        b2Vec2 velocity = 100.f * resultantVect;
        ballBody->SetLinearVelocity(velocity);
        balls.push_back(ballBody);
        fireTimer = 0;
    }
}

//for getting the collection of balls
vector<b2Body*> Ball::getBalls() {
    return balls;
}
//set the updated balls
void Ball::setBalls(vector<b2Body*>& tempBalls) {
    balls = tempBalls;
}
//drawing the balls
void Ball::draw(RenderWindow& window) {
    for (int i = 0; i < balls.size(); i++) {
        ball.setScale(0.09f, 0.09f);
        Vector2f ballPosition(balls[i]->GetPosition().x, balls[i]->GetPosition().y);
        ball.setPosition(ballPosition);
        window.draw(ball);
    }
}
