#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

//Paddle for releasing the balls

class Paddle {
    Sprite paddle;
    Texture paddleTex;
    b2Body* paddleBody;
    float paddleWidth;
    float paddleHeight;

public:
    //Constructor
    Paddle(b2World& world);
    //Left & Right movement 
    void move(float x);
    //Getting the curr Position
    b2Vec2 getPos();
    //Getting the pointer of the body 
    b2Body* getBody();
    //Drawing
    void draw(RenderWindow& window);
};

#endif
