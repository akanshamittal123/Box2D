#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

class Ball {
    vector<b2Body*>balls;
    Sprite ball;
    Texture ballTex;
    int fireTimer;
public:
    Ball();
    void fire(float x, float y, b2World& world, b2Vec2 force);
    vector<b2Body*> getBalls();
    void setBalls(vector<b2Body*>& tempBalls);
    void draw(RenderWindow& window);
};