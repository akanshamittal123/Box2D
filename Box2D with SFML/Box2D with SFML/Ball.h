#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

//Balls to shoot the bricks

class Ball {
    vector<b2Body*>balls;
    Sprite ball;
    Texture ballTex;
    // it is used to handle number of fires per click 
    int fireTimer;

public:
    //Constructor
    Ball();
    //mechanism to fire a ball
    void fire(float x, float y, b2World& world, RenderWindow&window, float &veloMag);
    //for getting the collection of balls
    vector<b2Body*> getBalls();
    //set the updated balls
    void setBalls(vector<b2Body*>& tempBalls);
    //drawing the balls
    void draw(RenderWindow& window);
};

#endif
